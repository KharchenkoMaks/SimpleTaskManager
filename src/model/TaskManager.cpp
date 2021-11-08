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
    tasks_[id] = t;
}

void TaskManager::Delete(int id) {
    tasks_.erase(id);
}

std::vector<std::pair<int, Task>> TaskManager::Show() {
    std::vector<std::pair<int, Task>> tasks;
    for (std::pair<const int, Task>& item : tasks_){
        tasks.push_back(std::pair<int, Task>(item.first, item.second));
    }
}