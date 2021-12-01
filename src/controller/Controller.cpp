//
// Created by Maksym Kharchenko on 29.11.2021.
//

#include "Controller.h"

Controller::Controller(std::unique_ptr<TaskManager> task_manager,
                       std::unique_ptr<TaskValidator> task_validator) :
                       task_manager_(std::move(task_manager)),
                       task_validator_(std::move(task_validator)) {

}

std::optional<TaskId> Controller::AddTask(const Task &task) {
    if (task_validator_->ValidateTask(task)){
        return task_manager_->Create(task);
    } else {
        return std::nullopt;
    }
}

void Controller::EditTask(const TaskId &task_id, const Task &task) {
    if (task_validator_->ValidateTask(task) && task_validator_->ValidateTaskId(task_id)) {
        if (task_manager_->IsTaskIdExist(task_id)) {
            task_manager_->Edit(task_id, task);
        }
    } else {
        throw std::invalid_argument("Invalid task or task_id was given.");
    }
}

void Controller::DeleteTask(const TaskId &task_id) {
    if (task_validator_->ValidateTaskId(task_id)) {
        if (task_manager_->IsTaskIdExist(task_id)){
            task_manager_->Delete(task_id);
        }
    } else {
        throw std::invalid_argument("Invalid task_id was given.");
    }
}

void Controller::CompleteTask(const TaskId &task_id) {
    if (task_validator_->ValidateTaskId(task_id)) {
        if (task_manager_->IsTaskIdExist(task_id)){
            task_manager_->Complete(task_id);
        }
    } else {
        throw std::invalid_argument("Invalid task_id was given.");
    }
}

std::optional<Task> Controller::GetTask(const TaskId &task_id) const {
    return task_manager_->GetTask(task_id);
}

std::string Controller::GetAllTasks() {
    std::string answer = "";

    auto tasks = task_manager_->Show();
    for (auto t : tasks){
        answer.append("ID: " + std::to_string(t.first.GetId()) + ", " + t.second.to_string());
    }

    return answer;
}
