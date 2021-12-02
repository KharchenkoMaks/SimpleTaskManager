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

std::optional<TaskId> Controller::AddSubTask(const Task& task, const TaskId& parent_id) {
    if (task_validator_->ValidateTask(task)) {
        if (model_->IsTaskIdExist(parent_id)) {
            return model_->AddSubTask(task, parent_id);
        }
    }
    return std::nullopt;
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

std::optional<Task> Controller::GetTask(const TaskId& task_id) const {
    std::optional<TaskTransfer> task = model_->GetTask(task_id);
    if (task.has_value()){
        return task->GetTask();
    } else {
        return std::nullopt;
    }
}

std::string Controller::GetAllTasks() {
    std::string answer = "";

    auto tasks = model_->GetTasks();
    for (auto t : tasks){
        if (!t.GetParentTaskId().has_value()) {
            answer.append(t.GetTaskId().to_string() + ", " + t.GetTask().to_string() + "\n");
        } else {
            answer.append("\t" + t.GetTaskId().to_string() + ", " + t.GetTask().to_string() + "\n");
        }
    }

    return answer;
}
