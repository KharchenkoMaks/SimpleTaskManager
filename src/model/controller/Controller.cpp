//
// Created by Maksym Kharchenko on 29.11.2021.
//

#include "Controller.h"

Controller::Controller(std::unique_ptr<IModel> model,
                       std::unique_ptr<TaskValidator> task_validator) :
                       model_(std::move(model)),
                       task_validator_(std::move(task_validator)),
                       tm_persistence_(std::make_unique<persistence::TasksPersistence>()) {

}

Controller::Controller(std::unique_ptr<IModel> model,
                       std::unique_ptr<TaskValidator> task_validator,
                       std::unique_ptr<persistence::TasksPersistence> tm_persistence) :
        model_(std::move(model)),
        task_validator_(std::move(task_validator)),
        tm_persistence_(std::move(tm_persistence)) {

}

std::pair<ControllerRequestResult, TaskId> Controller::AddTask(const Task& task) {
    if (task_validator_->ValidateTask(task)){
        std::pair<TaskActionResult, std::optional<TaskId>> result = model_->AddTask(task);
        if (result.first == TaskActionResult::SUCCESS) {
            return std::make_pair(ControllerRequestResult::SUCCESS, result.second.value());
        } else {
            return std::make_pair(FormControllerRequestResult(result.first).value(), TaskId::default_instance());
        }
    } else {
        return std::make_pair(ControllerRequestResult::FAIL_INVALID_TASK, TaskId::default_instance());
    }
}

std::pair<ControllerRequestResult, TaskId> Controller::AddSubTask(const Task& task, const TaskId& parent_id) {
    if (task_validator_->ValidateTask(task)) {
        std::pair<TaskActionResult, std::optional<TaskId>> result = model_->AddSubTask(task, parent_id);
        if (result.first == TaskActionResult::SUCCESS) {
            return std::make_pair(ControllerRequestResult::SUCCESS, result.second.value());
        } else {
            return std::make_pair(FormControllerRequestResult(result.first).value(), TaskId::default_instance());
        }
    }
    return std::make_pair(ControllerRequestResult::FAIL_INVALID_TASK, TaskId::default_instance());
}

ControllerRequestResult Controller::EditTask(const TaskId& task_id, const Task& task) {
    if (task_validator_->ValidateTask(task) && task_validator_->ValidateTaskId(task_id)) {
        TaskActionResult result = model_->EditTask(task_id, task);
        return FormControllerRequestResult(result).value();
    }
    return ControllerRequestResult::FAIL_INVALID_TASK;
}

ControllerRequestResult Controller::DeleteTask(const TaskId& task_id) {
    if (task_validator_->ValidateTaskId(task_id)) {
        TaskActionResult result = model_->DeleteTask(task_id);
        if (FormControllerRequestResult(result) == std::nullopt) {
            return ControllerRequestResult::FAIL_NOT_DELETED_SUBTASKS;
        } else {
            return FormControllerRequestResult(result).value();
        }
    }
    return ControllerRequestResult::FAIL_INVALID_TASK;
}

ControllerRequestResult Controller::DeleteTaskWithSubTasks(const TaskId& task_id) {
    if (task_validator_->ValidateTaskId(task_id)) {
        TaskActionResult result = model_->DeleteTask(task_id, true);
        return FormControllerRequestResult(result).value();
    }
    return ControllerRequestResult::FAIL_INVALID_TASK;
}

ControllerRequestResult Controller::CompleteTask(const TaskId& task_id) {
    if (task_validator_->ValidateTaskId(task_id)) {
        TaskActionResult result = model_->CompleteTask(task_id);
        if (FormControllerRequestResult(result) == std::nullopt) {
            return ControllerRequestResult::FAIL_UNCOMPLETED_SUBTASKS;
        } else {
            return FormControllerRequestResult(result).value();
        }
    }
    return ControllerRequestResult::FAIL_INVALID_TASK;
}

ControllerRequestResult Controller::CompleteTaskWithSubTasks(const TaskId& task_id) {
    if (task_validator_->ValidateTaskId(task_id)) {
        TaskActionResult result = model_->CompleteTask(task_id, true);
        return FormControllerRequestResult(result).value();
    }
    return ControllerRequestResult::FAIL_INVALID_TASK;
}

std::optional<TaskTransfer> Controller::GetTask(const TaskId& task_id) const {
    return model_->GetTask(task_id);
}

std::vector<TaskTransfer> Controller::GetAllTasks() {
    return model_->GetTasks();
}

ControllerRequestResult Controller::SetTaskLabel(const TaskId& task_id, const std::string& label) {
    TaskActionResult result = model_->SetTaskLabel(task_id, label);
    return FormControllerRequestResult(result).value();
}

ControllerRequestResult Controller::SaveToFile(const std::string& file_name) {
    persistence::SaveLoadStatus result = tm_persistence_->SaveToFile(file_name, model_->GetTasks());
    return FormControllerRequestResult(result);
}

ControllerRequestResult Controller::LoadFromFile(const std::string& file_name) {
    auto model_state = tm_persistence_->LoadFromFile(file_name);
    if (model_state.first != persistence::SaveLoadStatus::SUCCESS) {
        return FormControllerRequestResult(model_state.first);
    }
    if (model_->LoadModelState(model_state.second)) {
        return ControllerRequestResult::SUCCESS;
    } else {
        return ControllerRequestResult::FILE_DAMAGED;
    }
}
