//
// Created by Maksym Kharchenko on 08.11.2021.
//

#include "TaskManager.h"

TaskManager::TaskManager() {
    generator_ = IdGenerator();
}

TaskId TaskManager::Create(Task t) {
    TaskId task_id = generator_.CreateNewTaskId();
    tasks_.insert({ task_id, t });
    return task_id;
}

void TaskManager::Edit(TaskId id, Task t) {
    if (tasks_.find(id) != tasks_.end()) {
        tasks_.insert_or_assign(id, t);
    } else{
        throw std::invalid_argument("No task with such id.");
    }
}

void TaskManager::Delete(TaskId id) {
    if (tasks_.find(id) != tasks_.end()) {
        tasks_.erase(id);
    } else{
        throw std::invalid_argument("No task with such id.");
    }
}

void TaskManager::Complete(TaskId id) {
    this->Delete(id);
}

std::vector<std::pair<TaskId, Task>> TaskManager::Show() {
    std::vector<std::pair<TaskId, Task>> tasks;
    for (std::pair<const TaskId, Task>& item : tasks_){
        tasks.push_back(std::pair<TaskId, Task>(item.first, item.second));
    }
    return tasks;
}