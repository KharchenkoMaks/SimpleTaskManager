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

bool TaskManager::EditTask(const TaskId& id, const Task& t) {
    if (IsTaskIdExist(id)) {
        tasks_.insert_or_assign(id, t);
        return true;
    }
    return false;
}

bool TaskManager::DeleteTask(const TaskId& id) {
    if (IsTaskIdExist(id)) {
        tasks_.erase(id);
        return true;
    }
    return false;
}

bool TaskManager::CompleteTask(const TaskId& id) {
    if (IsTaskIdExist(id)) {
        auto task_iterator = tasks_.find(id);

        Task previous_task = task_iterator->second;
        if (previous_task.IsCompleted()){
            return false;
        }
        Task completed_task = Task::Create(previous_task.GetTitle(),
                                           previous_task.GetPriority(),
                                           previous_task.GetDueTime(),
                                           true,
                                           previous_task.GetLabel());

        tasks_.insert_or_assign(id, completed_task);
        return true;
    }
    return false;
}

std::vector<std::pair<TaskId, Task>> TaskManager::GetTasks() {
    std::vector<std::pair<TaskId, Task>> tasks;
    for (std::pair<const TaskId, Task>& item : tasks_){
        tasks.push_back(std::pair<TaskId, Task>(item.first, item.second));
    }
    return tasks;
}

bool TaskManager::IsTaskIdExist(const TaskId &task_id) {
    return tasks_.find(task_id) != tasks_.end();
}

std::optional<Task> TaskManager::GetTask(const TaskId& task_id) {
    if (IsTaskIdExist(task_id)){
        auto task_iterator = tasks_.find(task_id);
        return task_iterator->second;
    } else {
        return std::nullopt;
    }
}
