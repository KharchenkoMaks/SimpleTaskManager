//
// Created by Maksym Kharchenko on 08.11.2021.
//

#include "TaskManager.h"

TaskManager::TaskManager(std::unique_ptr<IdGenerator> generator)
    : generator_(std::move(generator)) {

}

TaskId TaskManager::Create(const Task& t) {
    TaskId task_id = generator_->CreateNewTaskId();
    tasks_.insert({ task_id, t });
    return task_id;
}

void TaskManager::Edit(const TaskId& id, const Task& t) {
    if (IsTaskIdExist(id)) {
        tasks_.insert_or_assign(id, t);
    } else{
        throw std::invalid_argument("No task with such id.");
    }
}

void TaskManager::Delete(const TaskId& id) {
    if (IsTaskIdExist(id)) {
        tasks_.erase(id);
    } else{
        throw std::invalid_argument("No task with such id.");
    }
}

void TaskManager::Complete(const TaskId& id) {
    if (IsTaskIdExist(id)) {
        auto task_iterator = tasks_.find(id);

        Task previous_task = task_iterator->second;
        Task completed_task = Task::Create(previous_task.GetTitle(),
                                           previous_task.GetPriority(),
                                           previous_task.GetDueTime(),
                                           true,
                                           previous_task.GetLabel());

        tasks_.insert_or_assign(id, completed_task);
    } else {
        throw std::invalid_argument("No task with such id.");
    }
}

std::vector<std::pair<TaskId, Task>> TaskManager::Show() {
    std::vector<std::pair<TaskId, Task>> tasks;
    for (std::pair<const TaskId, Task>& item : tasks_){
        tasks.push_back(std::pair<TaskId, Task>(item.first, item.second));
    }
    return tasks;
}

bool TaskManager::IsTaskIdExist(const TaskId &task_id) const {
    return tasks_.find(task_id) != tasks_.end();
}

std::optional<Task> TaskManager::GetTask(const TaskId& task_id) const {
    if (IsTaskIdExist(task_id)){
        auto task_iterator = tasks_.find(task_id);
        return task_iterator->second;
    } else {
        return std::nullopt;
    }
}
