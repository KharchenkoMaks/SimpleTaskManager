//
// Created by Maksym Kharchenko on 08.11.2021.
//

#include "TaskManager.h"

TaskManager::TaskManager() {
    next_id_ = 0;
}

int TaskManager::Create(Task t) {
    tasks_.insert({ ++next_id_, t });
    return next_id_;
}

void TaskManager::Edit(int id, Task t) {
    if (tasks_.find(id) != tasks_.end()) {
        tasks_[id] = t;
    } else{
        throw std::invalid_argument("No task with such id.");
    }
}

void TaskManager::Delete(int id) {
    if (tasks_.find(id) != tasks_.end()) {
        tasks_.erase(id);
    } else{
        throw std::invalid_argument("No task with such id.");
    }
}

std::vector<std::pair<int, Task>> TaskManager::Show() {
    std::vector<std::pair<int, Task>> tasks;
    for (std::pair<const int, Task>& item : tasks_){
        tasks.push_back(std::pair<int, Task>(item.first, item.second));
    }
    return tasks;
}