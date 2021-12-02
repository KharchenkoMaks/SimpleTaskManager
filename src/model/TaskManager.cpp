//
// Created by Maksym Kharchenko on 08.11.2021.
//

#include "TaskManager.h"

TaskManager::TaskManager(std::unique_ptr<IdGenerator> generator)
    : generator_(std::move(generator)) {

}

std::optional<TaskId> TaskManager::AddTask(const Task& t) {
    if (t.GetTitle().empty()){
        return std::nullopt;
    }
    TaskId task_id = generator_->CreateNewTaskId();
    tasks_.insert({ task_id, t });
    return task_id;
}

std::optional<TaskId> TaskManager::AddSubTask(const Task& task, const TaskId& parent_id) {
    if (task.GetTitle().empty()) {
        return std::nullopt;
    }
    if (GetTaskType(parent_id) != TaskType::Parent) {
        return std::nullopt;
    }
    SubTask subtask = SubTask::Create(task, parent_id);
    TaskId task_id = generator_->CreateNewTaskId();
    subtasks_.insert({ task_id, subtask });
    return task_id;
}

bool TaskManager::EditTask(const TaskId& id, const Task& t) {
    switch (GetTaskType(id)){
        case TaskType::Parent: {
            tasks_.insert_or_assign(id, t);
            return true;
        }
        case TaskType::Child: {
            std::optional<SubTask> subtask = GetSubTaskById(id);
            if (!subtask.has_value()) {
                return false;
            }
            SubTask new_subtask = SubTask::Create(t, subtask.value().GetParentTaskId());
            subtasks_.insert_or_assign(id, new_subtask);
            return true;
        }
        case TaskType::None: {
            return false;
        }
    }
}

bool TaskManager::DeleteTask(const TaskId& id) {
    switch (GetTaskType(id)) {
        case TaskType::Parent: {
            tasks_.erase(id);
            return true;
        }
        case TaskType::Child: {
            subtasks_.erase(id);
            return true;
        }
        case TaskType::None: {
            return false;
        }
    }
}

bool TaskManager::CompleteTask(const TaskId& id) {
    switch (GetTaskType(id)){
        case TaskType::Parent: {
            std::optional<Task> task_to_complete = GetTaskById(id);
            if (!task_to_complete.has_value()) {
                return false;
            }
            tasks_.insert_or_assign(id, MakeTaskCompleted(task_to_complete.value()));
            return true;
        }
        case TaskType::Child: {
            SubTask subtask = subtasks_.find(id)->second;
            subtasks_.insert_or_assign(id,
                                       SubTask::Create(
                                               MakeTaskCompleted(subtask.GetTaskParameters()),
                                               subtask.GetParentTaskId()));
            return true;
        }
        case TaskType::None: {
            return false;
        }
    }
}

std::vector<TaskTransfer> TaskManager::GetTasks() {
    std::vector<TaskTransfer> tasks;
    for (const auto& task_item : tasks_) {
        tasks.push_back(TaskTransfer::Create(task_item.first, task_item.second));
        for (const auto& subtask_item : GetTaskSubTasks(task_item.first).value()) {
            tasks.push_back(subtask_item);
        }
    }
    return tasks;
}

bool TaskManager::IsTaskIdExist(const TaskId &task_id) {
    return tasks_.find(task_id) != tasks_.end() || subtasks_.find(task_id) != subtasks_.end();
}

std::optional<TaskTransfer> TaskManager::GetTask(const TaskId& task_id) {
    switch (GetTaskType(task_id)) {
        case TaskType::Parent: {
            auto task_iterator = tasks_.find(task_id);
            return TaskTransfer::Create(task_iterator->first, task_iterator->second);
        }
        case TaskType::Child: {
            auto subtask_iterator = subtasks_.find(task_id);
            return TaskTransfer::Create(subtask_iterator->first,
                                        subtask_iterator->second.GetTaskParameters(),
                                        subtask_iterator->second.GetParentTaskId());
        }
        case TaskType::None: {
            return std::nullopt;
        }
    }
}

TaskManager::TaskType TaskManager::GetTaskType(const TaskId& task_id) const {
    if (tasks_.find(task_id) != tasks_.end()) {
        return TaskType::Parent;
    } else if (subtasks_.find(task_id) != subtasks_.end()) {
        return TaskType::Child;
    } else {
        return TaskType::None;
    }
}

std::optional<SubTask> TaskManager::GetSubTaskById(const TaskId& task_id) const {
    if (GetTaskType(task_id) == TaskType::Child){
        auto task_iterator = subtasks_.find(task_id);
        return task_iterator->second;
    } else {
        return std::nullopt;
    }
}

std::optional<Task> TaskManager::GetTaskById(const TaskId& task_id) const {
    if (GetTaskType(task_id) == TaskType::Parent){
        auto task_iterator = tasks_.find(task_id);
        return task_iterator->second;
    } else {
        return std::nullopt;
    }
}

Task TaskManager::MakeTaskCompleted(const Task& task) {
    return Task::Create(task.GetTitle(), task.GetPriority(), task.GetDueTime(), true, task.GetLabel());
}

std::optional<std::vector<TaskTransfer>> TaskManager::GetTaskSubTasks(const TaskId& parent_task_id) const {
    std::vector<TaskTransfer> subtasks;
    if (GetTaskType(parent_task_id) != TaskType::Parent){
        return std::nullopt;
    }
    for (const auto& item : subtasks_) {
        if (item.second.GetParentTaskId() == parent_task_id) {
            subtasks.push_back(TaskTransfer::Create(item.first, item.second.GetTaskParameters(), item.second.GetParentTaskId()));
        }
    }
    return subtasks;
}
