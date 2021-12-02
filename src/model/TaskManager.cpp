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
            std::optional<SubTask> subtask = GetSubTask(id);
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
            Task task = tasks_.find(id)->second;
            tasks_.insert_or_assign(id, MakeTaskCompleted(task));
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

std::vector<std::pair<TaskId, Task>> TaskManager::GetTasks() {
    std::vector<std::pair<TaskId, Task>> tasks;
    for (std::pair<const TaskId, Task>& item : tasks_){
        tasks.push_back(std::pair<TaskId, Task>(item.first, item.second));
    }
    return tasks;
}

bool TaskManager::IsTaskIdExist(const TaskId &task_id) {
    return tasks_.find(task_id) != tasks_.end() || subtasks_.find(task_id) != subtasks_.end();
}

std::optional<Task> TaskManager::GetTask(const TaskId& task_id) {
    if (IsTaskIdExist(task_id)){
        auto task_iterator = tasks_.find(task_id);
        return task_iterator->second;
    } else {
        return std::nullopt;
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

std::optional<SubTask> TaskManager::GetSubTask(const TaskId& task_id) const {
    if (GetTaskType(task_id) == TaskType::Child){
        auto task_iterator = subtasks_.find(task_id);
        return task_iterator->second;
    } else {
        return std::nullopt;
    }
}

Task TaskManager::MakeTaskCompleted(const Task& task) {
    return Task::Create(task.GetTitle(), task.GetPriority(), task.GetDueTime(), true, task.GetLabel());
}
