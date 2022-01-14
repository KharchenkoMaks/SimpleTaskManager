//
// Created by Maksym Kharchenko on 08.11.2021.
//

#include "TaskManager.h"
#include "utilities/TaskComparators.h"
#include "TaskNodeFactoryMethod.h"

using namespace model;

TaskManager::TaskManager(std::unique_ptr<IdGenerator> generator) :
                        generator_(std::move(generator)),
                        task_validator_(std::make_unique<TaskValidator>()) {

}

TaskManager::TaskManager(std::unique_ptr<IdGenerator> generator,
                         std::unique_ptr<TaskValidator> task_validator) :
        generator_(std::move(generator)),
        task_validator_(std::move(task_validator)) {

}

std::pair<TaskActionResult, TaskId> TaskManager::AddTask(const Task& task) {
    if (!task_validator_->ValidateTask(task)) {
        return std::pair(TaskActionResult::FAIL_INVALID_TASK, TaskId::default_instance());
    }

    TaskId task_id = generator_->CreateNewTaskId();
    tasks_.insert({ task_id, model::CreateTaskNode(task) });
    return std::pair(TaskActionResult::SUCCESS, task_id);
}

std::pair<TaskActionResult, TaskId> TaskManager::AddSubTask(const Task& task, const TaskId& parent_id) {
    if (!task_validator_->ValidateTask(task)) {
        return std::pair(TaskActionResult::FAIL_INVALID_TASK, TaskId::default_instance());
    }

    auto parent_task = tasks_.find(parent_id);
    if (parent_task == tasks_.end()) {
        return std::pair(TaskActionResult::FAIL_NO_SUCH_TASK, TaskId::default_instance());
    }

    TaskId subtask_id = generator_->CreateNewTaskId();
    tasks_.insert({ subtask_id, model::CreateTaskNode(task, parent_id) });
    return std::pair(TaskActionResult::SUCCESS, subtask_id);
}

TaskActionResult TaskManager::EditTask(const TaskId& id, const Task& task) {
    if (!task_validator_->ValidateTask(task)) {
        return TaskActionResult::FAIL_INVALID_TASK;
    }

    auto editing_task = tasks_.find(id);
    if (editing_task == tasks_.end())
        return TaskActionResult::FAIL_NO_SUCH_TASK;

    editing_task->second.set_allocated_task(new Task(task));
    return TaskActionResult::SUCCESS;
}

TaskActionResult TaskManager::DeleteTask(const TaskId& id, bool force_delete_subtasks) {
    auto deleting_task = tasks_.find(id);
    if (deleting_task == tasks_.end())
        return TaskActionResult::FAIL_NO_SUCH_TASK;

    auto search_child_rule = [&id](const std::pair<TaskId, TaskNode>& task) {
        return task.second.parent_id() == id;
    };
    if (force_delete_subtasks) {
        auto subtask = std::find_if(tasks_.begin(), tasks_.end(), search_child_rule);
        while (subtask != tasks_.end()) {
            this->DeleteTask(subtask->first, true);
            subtask = std::find_if(tasks_.begin(), tasks_.end(), search_child_rule);
        }
    } else if (std::find_if(tasks_.begin(), tasks_.end(), search_child_rule) != tasks_.end()) {
        return TaskActionResult::FAIL_CONTROVERSIAL_SUBTASKS;
    }

    deleted_tasks_.insert_or_assign(deleting_task->first, deleting_task->second);
    tasks_.erase(deleting_task);
    return TaskActionResult::SUCCESS;
}

TaskActionResult TaskManager::CompleteTask(const TaskId& id, bool force_complete_subtasks) {
    auto completing_task = tasks_.find(id);
    if (completing_task == tasks_.end())
        return TaskActionResult::FAIL_NO_SUCH_TASK;

    auto search_uncompleted_child_rule = [&id](const std::pair<TaskId, TaskNode>& task) {
        return task.second.parent_id() == id && !task.second.task().completed();
    };

    if (force_complete_subtasks) {
        for (const auto& task : tasks_)
            if (task.second.parent_id() == id && !task.second.task().completed())
                this->CompleteTask(task.first, true);
    } else if (std::find_if(tasks_.begin(), tasks_.end(), search_uncompleted_child_rule) != tasks_.end()) {
        return TaskActionResult::FAIL_CONTROVERSIAL_SUBTASKS;
    }

    Task task_to_complete = completing_task->second.task();
    task_to_complete.set_completed(true);
    completing_task->second.set_allocated_task(new Task(task_to_complete));
    return TaskActionResult::SUCCESS;
}

std::vector<TaskTransfer> TaskManager::GetTasks() {
    std::vector<TaskTransfer> tasks;
    for (const auto& task : tasks_) {
        if (!task.second.has_parent_id()) {
            auto adding_tasks = GetAllTaskChildren(task.first);
            tasks.insert(tasks.end(), adding_tasks.begin(), adding_tasks.end());
        }
    }
    return tasks;
}

bool TaskManager::IsTaskExist(const TaskId& task_id) {
    return tasks_.find(task_id) != tasks_.end();
}

std::optional<TaskTransfer> TaskManager::GetTask(const TaskId& task_id) {
    auto task = tasks_.find(task_id);
    if (task == tasks_.end())
        return std::nullopt;

    return CreateTaskTransferFromTask(task);
}

TaskActionResult TaskManager::AddTaskLabel(const TaskId& id, const std::string& label) {
    auto task_to_add_label = tasks_.find(id);
    if (task_to_add_label == tasks_.end())
        return TaskActionResult::FAIL_NO_SUCH_TASK;

    Task task = task_to_add_label->second.task();
    task.set_label(label);
    task_to_add_label->second.set_allocated_task(new Task(task));
    return TaskActionResult::SUCCESS;
}

bool TaskManager::LoadModelState(const std::vector<TaskTransfer>& tasks) {
    std::map<TaskId, TaskNode> tasks_to_add;
    TaskId max_id;
    max_id.set_id(1);
    for (const auto& task : tasks) {
        if (!task.has_task() || !task.has_task_id() || !task_validator_->ValidateTask(task.task())) {
            return false;
        }
        if (task.task_id().id() > max_id.id())
            max_id = task.task_id();

        tasks_to_add.insert_or_assign(task.task_id(), model::CreateTaskNode(task));
    }
    generator_->SetLastTaskId(max_id);
    tasks_.swap(tasks_to_add);
    return true;
}

std::vector<TaskTransfer> TaskManager::GetAllTaskChildren(const TaskId& task_id) {
    std::vector<TaskTransfer> tasks;
    auto main_task = tasks_.find(task_id);
    if (main_task == tasks_.end())
        return tasks;

    tasks.push_back(CreateTaskTransferFromTask(main_task));
    for (const auto& task : tasks_) {
        if (task.second.parent_id() == task_id) {
            auto task_children = GetAllTaskChildren(task.first);
            tasks.insert(tasks.end(), task_children.begin(), task_children.end());
        }
    }

    return tasks;
}

TaskTransfer TaskManager::CreateTaskTransferFromTask(const std::map<TaskId, TaskNode>::iterator task) {
    TaskTransfer task_transfer;
    task_transfer.set_allocated_task_id(new TaskId(task->first));
    task_transfer.set_allocated_task(new Task(task->second.task()));
    if (task->second.has_parent_id()) {
        task_transfer.set_allocated_parent_id(new TaskId(task->second.parent_id()));
    }
    return task_transfer;
}
