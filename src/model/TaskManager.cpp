//
// Created by Maksym Kharchenko on 08.11.2021.
//

#include "TaskManager.h"

TaskManager::TaskManager(std::unique_ptr<IdGenerator> generator)
    : generator_(std::move(generator)) {

}

std::pair<TaskActionResult, std::optional<TaskId>> TaskManager::AddTask(const Task& t) {
    if (t.GetTitle().empty()){
        return std::pair(TaskActionResult::FAIL_INVALID_TASK, std::nullopt);
    }
    TaskId task_id = generator_->CreateNewTaskId();
    tasks_.insert({ task_id, t });
    return std::pair(TaskActionResult::SUCCESS, task_id);
}

std::pair<TaskActionResult, std::optional<TaskId>> TaskManager::AddSubTask(const Task& task, const TaskId& parent_id) {
    if (task.GetTitle().empty()) {
        return std::pair(TaskActionResult::FAIL_INVALID_TASK, std::nullopt);
    }
    if (GetTaskType(parent_id) != TaskType::kParent) {
        return std::pair(TaskActionResult::FAIL_NO_SUCH_TASK, std::nullopt);
    }
    SubTask subtask = SubTask::Create(task, parent_id);
    TaskId task_id = generator_->CreateNewTaskId();
    subtasks_.insert({ task_id, subtask });
    return std::pair(TaskActionResult::SUCCESS, task_id);
}

TaskActionResult TaskManager::EditTask(const TaskId& id, const Task& t) {
    switch (GetTaskType(id)){
        case TaskType::kParent: {
            tasks_.insert_or_assign(id, t);
            return TaskActionResult::SUCCESS;
        }
        case TaskType::kChild: {
            std::optional<SubTask> subtask = GetSubTaskById(id);
            SubTask new_subtask = SubTask::Create(t, subtask.value().GetParentTaskId());
            subtasks_.insert_or_assign(id, new_subtask);
            return TaskActionResult::SUCCESS;
        }
        default: {
            return TaskActionResult::FAIL_NO_SUCH_TASK;
        }
    }
}

void TaskManager::DeleteSubTasks(const TaskId& parent_id) {
    std::optional<std::vector<TaskId>> subtasks_to_delete = GetAllTaskSubTaskIds(parent_id);
    if (subtasks_to_delete.has_value()) {
        for (const auto& subtask_id : subtasks_to_delete.value()) {
            DeleteTask(subtask_id);
        }
    }
}

TaskActionResult TaskManager::DeleteTask(const TaskId& id, bool force_delete_subtasks) {
    switch (GetTaskType(id)) {
        case TaskType::kParent: {
            if (force_delete_subtasks) {
                DeleteSubTasks(id);
            } else {
                auto find_undeleted_subtasks = [&id](std::pair<TaskId, SubTask> p) {
                    return p.second.GetParentTaskId() == id;
                };
                if (std::find_if(subtasks_.begin(), subtasks_.end(), find_undeleted_subtasks) != subtasks_.end()) {
                    return TaskActionResult::FAIL_CONTROVERSIAL_SUBTASKS;
                }
            }

            auto task_iterator = tasks_.find(id);
            tasks_.erase(task_iterator);
            deleted_tasks_.insert_or_assign(task_iterator->first, task_iterator->second);

            return TaskActionResult::SUCCESS;
        }
        case TaskType::kChild: {
            auto subtask_iterator = subtasks_.find(id);
            subtasks_.erase(subtask_iterator);
            deleted_subtasks_.insert_or_assign(subtask_iterator->first, subtask_iterator->second);
            return TaskActionResult::SUCCESS;
        }
        default: {
            return TaskActionResult::FAIL_NO_SUCH_TASK;
        }
    }
}

void TaskManager::CompleteSubTasks(const TaskId& parent_id) {
    std::optional<std::vector<TaskId>> subtasks_to_complete = GetAllTaskSubTaskIds(parent_id);
    if (subtasks_to_complete.has_value()) {
        for (const auto& subtask_id : subtasks_to_complete.value()) {
            CompleteTask(subtask_id);
        }
    }
}

TaskActionResult TaskManager::CompleteTask(const TaskId& id, bool force_complete_subtasks) {
    switch (GetTaskType(id)){
        case TaskType::kParent: {
            if (force_complete_subtasks) {
                CompleteSubTasks(id);
            } else {
                auto find_uncompleted_subtasks = [&id](std::pair<TaskId, SubTask> p){
                    return p.second.GetParentTaskId() == id && !p.second.GetTaskParameters().IsCompleted();
                };
                if (std::find_if(subtasks_.begin(), subtasks_.end(), find_uncompleted_subtasks) != subtasks_.end()) {
                    return TaskActionResult::FAIL_CONTROVERSIAL_SUBTASKS;
                }
            }

            std::optional<Task> task_to_complete = GetTaskById(id);
            tasks_.insert_or_assign(id, CompleteTask(task_to_complete.value()));

            return TaskActionResult::SUCCESS;
        }
        case TaskType::kChild: {
            SubTask subtask = GetSubTaskById(id).value();
            subtasks_.insert_or_assign(id,
                                       SubTask::Create(
                                               CompleteTask(subtask.GetTaskParameters()),
                                               subtask.GetParentTaskId()));
            return TaskActionResult::SUCCESS;
        }
        default: {
            return TaskActionResult::FAIL_NO_SUCH_TASK;
        }
    }
}

std::vector<TaskTransfer> TaskManager::GetTasks() {
    std::vector<TaskTransfer> tasks;
    for (const auto& task_item : tasks_) {
        tasks.push_back(CreateTaskTransfer(task_item.first, task_item.second));
        std::vector<TaskTransfer> subtasks = GetTaskSubTasks(task_item.first).second;
        for (const auto& subtask_item : subtasks) {
            tasks.push_back(subtask_item);
        }
    }
    return tasks;
}

bool TaskManager::IsTaskExist(const TaskId &task_id) {
    auto task_type = GetTaskType(task_id);
    return task_type == TaskType::kParent || task_type == TaskType::kChild;
}

std::optional<TaskTransfer> TaskManager::GetTask(const TaskId& task_id) {
    switch (GetTaskType(task_id)) {
        case TaskType::kParent: {
            auto task_iterator = tasks_.find(task_id);
            return TaskTransfer::Create(task_iterator->first, task_iterator->second);
        }
        case TaskType::kChild: {
            auto subtask_iterator = subtasks_.find(task_id);
            return TaskTransfer::Create(subtask_iterator->first,
                                        subtask_iterator->second.GetTaskParameters(),
                                        subtask_iterator->second.GetParentTaskId());
        }
        default: {
            return std::nullopt;
        }
    }
}

TaskManager::TaskType TaskManager::GetTaskType(const TaskId& task_id) const {
    if (deleted_tasks_.find(task_id) != deleted_tasks_.end() || deleted_subtasks_.find(task_id) != deleted_subtasks_.end()) {
        return TaskType::kDeleted;
    } else if (tasks_.find(task_id) != tasks_.end()) {
        return TaskType::kParent;
    } else if (subtasks_.find(task_id) != subtasks_.end()) {
        return TaskType::kChild;
    } else {
        return TaskType::kNone;
    }
}

std::optional<SubTask> TaskManager::GetSubTaskById(const TaskId& task_id) const {
    if (GetTaskType(task_id) == TaskType::kChild){
        auto task_iterator = subtasks_.find(task_id);
        return task_iterator->second;
    } else {
        return std::nullopt;
    }
}

std::optional<Task> TaskManager::GetTaskById(const TaskId& task_id) const {
    if (GetTaskType(task_id) == TaskType::kParent){
        auto task_iterator = tasks_.find(task_id);
        return task_iterator->second;
    } else {
        return std::nullopt;
    }
}

Task TaskManager::CompleteTask(const Task& task) {
    return Task::Create(task.GetTitle(), task.GetPriority(), task.GetDueTime(), true, task.GetLabel());
}

std::pair<TaskActionResult, std::vector<TaskTransfer>> TaskManager::GetTaskSubTasks(const TaskId& parent_task_id) {
    std::vector<TaskTransfer> subtasks;
    if (GetTaskType(parent_task_id) != TaskType::kParent){
        return std::pair(TaskActionResult::FAIL_NO_SUCH_TASK, subtasks);
    }
    for (const auto& item : subtasks_) {
        if (item.second.GetParentTaskId() == parent_task_id) {
            subtasks.push_back(CreateTaskTransfer(item.first, item.second));
        }
    }
    return std::pair(TaskActionResult::SUCCESS, subtasks);
}

TaskActionResult TaskManager::SetTaskLabel(const TaskId& id, const std::string& label) {
    switch (GetTaskType(id)) {
        case TaskType::kParent: {
            Task task_to_label = GetTaskById(id).value();
            tasks_.insert_or_assign(id, SetLabel(task_to_label, label));
            return TaskActionResult::SUCCESS;
        }
        case TaskType::kChild: {
            SubTask task_to_label = GetSubTaskById(id).value();
            SubTask task_with_label =
                    SubTask::Create(SetLabel(task_to_label.GetTaskParameters(), label), task_to_label.GetParentTaskId());
            subtasks_.insert_or_assign(id, task_with_label);
            return TaskActionResult::SUCCESS;
        }
        default: {
            return TaskActionResult::FAIL_NO_SUCH_TASK;
        }
    }
}

Task TaskManager::SetLabel(const Task& task, const std::string& label) {
    return Task::Create(task.GetTitle(),
                        task.GetPriority(),
                        task.GetDueTime(),
                        task.IsCompleted(),
                        label);
}

std::optional<std::vector<TaskId>> TaskManager::GetAllTaskSubTaskIds(const TaskId& parent_id) {
    if (GetTaskType(parent_id) != TaskType::kParent) {
        return std::nullopt;
    }
    std::vector<TaskId> subtasks;
    for (const auto& item : subtasks_) {
        if (item.second.GetParentTaskId() == parent_id) {
            subtasks.push_back(item.first);
        }
    }
    return subtasks;
}

TaskTransfer TaskManager::CreateTaskTransfer(const TaskId& id, const Task& task) {
    return TaskTransfer::Create(id, task);
}

TaskTransfer TaskManager::CreateTaskTransfer(const TaskId& id, const SubTask& task) {
    return TaskTransfer::Create(id, task.GetTaskParameters(), task.GetParentTaskId());
}