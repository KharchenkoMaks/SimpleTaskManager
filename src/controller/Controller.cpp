//
// Created by Maksym Kharchenko on 29.11.2021.
//

#include "Controller.h"

Controller::Controller(std::unique_ptr<IModel> model,
                       std::unique_ptr<TaskValidator> task_validator) :
                       model_(std::move(model)),
                       task_validator_(std::move(task_validator)) {

}

std::optional<TaskId> Controller::AddTask(const Task &task) {
    if (task_validator_->ValidateTask(task)){
        return model_->AddTask(task);
    } else {
        return std::nullopt;
    }
}

bool Controller::EditTask(const TaskId &task_id, const Task &task) {
    if (task_validator_->ValidateTask(task) && task_validator_->ValidateTaskId(task_id)) {
        if (model_->IsTaskIdExist(task_id)) {
            return model_->EditTask(task_id, task);
        }
    }
    return false;
}

bool Controller::DeleteTask(const TaskId &task_id) {
    if (task_validator_->ValidateTaskId(task_id)) {
        if (model_->IsTaskIdExist(task_id)){
            return model_->DeleteTask(task_id);
        }
    }
    return false;
}

bool Controller::CompleteTask(const TaskId &task_id) {
    if (task_validator_->ValidateTaskId(task_id)) {
        if (model_->IsTaskIdExist(task_id)){
            return model_->CompleteTask(task_id);
        }
    }
    return false;
}

std::optional<Task> Controller::GetTask(const TaskId &task_id) const {
    return model_->GetTask(task_id);
}

std::string Controller::GetAllTasks() {
    std::string answer = "";

    auto tasks = model_->GetTasks();
    for (auto t : tasks){
        answer.append("ID: " + std::to_string(t.first.GetId()) + ", " + t.second.to_string());
    }

    return answer;
}
