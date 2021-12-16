//
// Created by Maksym Kharchenko on 08.11.2021.
//

#include "TaskManager.h"
#include "utilities/TaskUtilities.h"

TaskManager::TaskManager(std::unique_ptr<IdGenerator> generator) :
                        generator_(std::move(generator)),
                        task_validator_(std::make_unique<TaskValidator>()) {

}

TaskManager::TaskManager(std::unique_ptr<IdGenerator> generator,
                         std::unique_ptr<TaskValidator> task_validator) :
        generator_(std::move(generator)),
        task_validator_(std::move(task_validator)) {

}

std::pair<TaskActionResult, std::optional<TaskId>> TaskManager::AddTask(const Task& task) {
    if (!task_validator_->ValidateTask(task)) {
        return std::pair(TaskActionResult::FAIL_INVALID_TASK, std::nullopt);
    }
    TaskId task_id = generator_->CreateNewTaskId();
    tasks_.insert({ task_id, MainTask::Create(task) });
    return std::pair(TaskActionResult::SUCCESS, task_id);
}

std::pair<TaskActionResult, std::optional<TaskId>> TaskManager::AddSubTask(const Task& task, const TaskId& parent_id) {
    if (!task_validator_->ValidateTask(task)) {
        return std::pair(TaskActionResult::FAIL_INVALID_TASK, std::nullopt);
    }
    auto parent_task = tasks_.find(parent_id);
    if (parent_task == tasks_.end()) {
        return std::pair(TaskActionResult::FAIL_NO_SUCH_TASK, std::nullopt);
    }
    TaskId subtask_id = generator_->CreateNewTaskId();
    parent_task->second.AddSubTask(subtask_id, task);
    return std::pair(TaskActionResult::SUCCESS, subtask_id);
}

TaskActionResult TaskManager::EditTask(const TaskId& id, const Task& task) {
    if (!task_validator_->ValidateTask(task)) {
        return TaskActionResult::FAIL_INVALID_TASK;
    }
    if (tasks_.find(id) != tasks_.end()) {
        auto main_task = tasks_.find(id);
        main_task->second.EditTask(task);
        return TaskActionResult::SUCCESS;
    } else if (GetMainTaskWithSubTask(id).has_value()) {
        auto subtask = GetMainTaskWithSubTask(id).value();
        subtask->second.EditSubTask(id, task);
        return TaskActionResult::SUCCESS;
    } else {
        return TaskActionResult::FAIL_NO_SUCH_TASK;
    }
}

TaskActionResult TaskManager::DeleteTask(const TaskId& id, bool force_delete_subtasks) {
    if (tasks_.find(id) != tasks_.end()) {
        auto task = tasks_.find(id);
        if (!force_delete_subtasks) {
            if (task->second.SubTaskCount() > 0) {
                return TaskActionResult::FAIL_CONTROVERSIAL_SUBTASKS;
            }
        }
        tasks_.erase(task);
        deleted_tasks_.insert_or_assign(task->first, task->second);
        return TaskActionResult::SUCCESS;
    } else if (GetMainTaskWithSubTask(id).has_value()) {
        auto task = GetMainTaskWithSubTask(id).value();
        task->second.DeleteSubTask(id);
        return TaskActionResult::SUCCESS;
    } else {
        return TaskActionResult::FAIL_NO_SUCH_TASK;
    }
}

TaskActionResult TaskManager::CompleteTask(const TaskId& id, bool force_complete_subtasks) {
    if (tasks_.find(id) != tasks_.end()) {
        auto task = tasks_.find(id);
        if (force_complete_subtasks) {
            task->second.CompleteAllSubTasks();
        } else {
            if (!task->second.AreAllSubTasksCompleted()) {
                return TaskActionResult::FAIL_CONTROVERSIAL_SUBTASKS;
            }
        }
        task->second.CompleteTask();
        return TaskActionResult::SUCCESS;
    } else if (GetMainTaskWithSubTask(id).has_value()) {
        auto task = GetMainTaskWithSubTask(id).value();
        task->second.CompleteSubTask(id);
        return TaskActionResult::SUCCESS;
    } else {
        return TaskActionResult::FAIL_NO_SUCH_TASK;
    }
}

std::vector<TaskTransfer> TaskManager::GetTasks() {
    std::vector<TaskTransfer> tasks;
    for (const auto& task_item : tasks_) {
        std::vector<TaskTransfer> task_with_subtasks = CreateTaskTransferFromMainTask(task_item.first, task_item.second);
        tasks.insert(tasks.end(), task_with_subtasks.begin(), task_with_subtasks.end());
    }
    return tasks;
}

bool TaskManager::IsTaskExist(const TaskId& task_id) {
    return tasks_.find(task_id) != tasks_.end() || GetMainTaskWithSubTask(task_id).has_value();
}

std::optional<TaskTransfer> TaskManager::GetTask(const TaskId& task_id) {
    if (tasks_.find(task_id) != tasks_.end()) {
        auto task = tasks_.find(task_id);
        return CreateTaskTransferFromTask(task->first, task->second.GetTask());
    } else if (GetMainTaskWithSubTask(task_id).has_value()) {
        auto parent_task = GetMainTaskWithSubTask(task_id).value();
        auto subtask = parent_task->second.GetSubTask(task_id).value();
        return CreateTaskTransferFromSubTask(subtask.first, subtask.second, parent_task->first);
    } else {
        return std::nullopt;
    }
}

std::pair<TaskActionResult, std::vector<TaskTransfer>> TaskManager::GetTaskSubTasks(const TaskId& parent_task_id) {
    std::vector<TaskTransfer> subtasks_transfer;
    auto parent_task = tasks_.find(parent_task_id);
    if (parent_task == tasks_.end()){
        return std::pair(TaskActionResult::FAIL_NO_SUCH_TASK, subtasks_transfer);
    }
    auto subtasks = parent_task->second.GetSubTasks();
    for (const auto& subtask : subtasks) {
        subtasks_transfer.push_back(CreateTaskTransferFromSubTask(subtask.first, subtask.second, parent_task_id));
    }
    return std::pair(TaskActionResult::SUCCESS, subtasks_transfer);
}

TaskActionResult TaskManager::SetTaskLabel(const TaskId& id, const std::string& label) {
    if (tasks_.find(id) != tasks_.end()) {
        auto task = tasks_.find(id);
        task->second.SetTaskLabel(label);
        return TaskActionResult::SUCCESS;
    } else if (GetMainTaskWithSubTask(id).has_value()) {
        auto task = GetMainTaskWithSubTask(id).value();
        task->second.SetSubTaskLabel(id, label);
        return TaskActionResult::SUCCESS;
    } else {
        return TaskActionResult::FAIL_NO_SUCH_TASK;
    }
}

std::optional<std::map<TaskId, MainTask>::iterator> TaskManager::GetMainTaskWithSubTask(const TaskId& subtask_id) {
    for (const auto& task : tasks_) {
        if (task.second.ContainsSubTask(subtask_id)) {
            return tasks_.find(task.first);
        }
    }
    return std::nullopt;
}

std::vector<TaskTransfer> TaskManager::CreateTaskTransferFromMainTask(const TaskId& task_id, const MainTask& main_task) {
    std::vector<TaskTransfer> tasks;
    tasks.push_back(CreateTaskTransferFromTask(task_id, main_task.GetTask()));
    auto subtasks = main_task.GetSubTasks();
    for (const auto& subtask : subtasks) {
        tasks.push_back(CreateTaskTransferFromSubTask(subtask.first, subtask.second, task_id));
    }
    return tasks;
}

TaskTransfer TaskManager::CreateTaskTransferFromTask(const TaskId& task_id, const Task& task) {
    TaskTransfer task_transfer;
    task_transfer.set_allocated_task_id(new TaskId(task_id));
    task_transfer.set_allocated_task(new Task(task));
    return task_transfer;
}

TaskTransfer TaskManager::CreateTaskTransferFromSubTask(const TaskId& task_id, const Task& task, const TaskId& parent_id) {
    TaskTransfer task_transfer;
    task_transfer.set_allocated_task_id(new TaskId(task_id));
    task_transfer.set_allocated_task(new Task(task));
    task_transfer.set_allocated_parent_id(new TaskId(parent_id));
    return task_transfer;
}
