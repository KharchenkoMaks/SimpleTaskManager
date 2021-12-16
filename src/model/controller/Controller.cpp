//
// Created by Maksym Kharchenko on 29.11.2021.
//

#include "Controller.h"

Controller::Controller(std::unique_ptr<IModel> model,
                       std::unique_ptr<TaskValidator> task_validator) :
                       model_(std::move(model)),
                       task_validator_(std::move(task_validator)),
                       tm_persistence_(std::make_unique<TaskManagerPersistence>()) {

}

Controller::Controller(std::unique_ptr<IModel> model,
                       std::unique_ptr<TaskValidator> task_validator,
                       std::unique_ptr<TaskManagerPersistence> tm_persistence) :
        model_(std::move(model)),
        task_validator_(std::move(task_validator)),
        tm_persistence_(std::move(tm_persistence)) {

}

std::pair<TaskActionResult, std::optional<TaskId>> Controller::AddTask(const Task &task) {
    if (task_validator_->ValidateTask(task)){
        return model_->AddTask(task);
    } else {
        return std::pair(TaskActionResult::FAIL_INVALID_TASK, std::nullopt);
    }
}

std::pair<TaskActionResult, std::optional<TaskId>> Controller::AddSubTask(const Task& task, const TaskId& parent_id) {
    if (task_validator_->ValidateTask(task)) {
        return model_->AddSubTask(task, parent_id);
    }
    return std::pair(TaskActionResult::FAIL_INVALID_TASK, std::nullopt);
}

TaskActionResult Controller::EditTask(const TaskId &task_id, const Task &task) {
    if (task_validator_->ValidateTask(task) && task_validator_->ValidateTaskId(task_id)) {
        return model_->EditTask(task_id, task);
    }
    return TaskActionResult::FAIL_INVALID_TASK;
}

TaskActionResult Controller::DeleteTask(const TaskId &task_id) {
    if (task_validator_->ValidateTaskId(task_id)) {
        return model_->DeleteTask(task_id);
    }
    return TaskActionResult::FAIL_INVALID_TASK;
}

TaskActionResult Controller::DeleteTaskWithSubTasks(const TaskId& task_id) {
    if (task_validator_->ValidateTaskId(task_id)) {
        model_->DeleteTask(task_id, true);
    }
    return TaskActionResult::FAIL_INVALID_TASK;
}

TaskActionResult Controller::CompleteTask(const TaskId &task_id) {
    if (task_validator_->ValidateTaskId(task_id)) {
        return model_->CompleteTask(task_id);
    }
    return TaskActionResult::FAIL_INVALID_TASK;
}

TaskActionResult Controller::CompleteTaskWithSubTasks(const TaskId& task_id) {
    if (task_validator_->ValidateTaskId(task_id)) {
        model_->CompleteTask(task_id, true);
    }
    return TaskActionResult::FAIL_INVALID_TASK;
}

std::optional<TaskTransfer> Controller::GetTask(const TaskId& task_id) const {
    return model_->GetTask(task_id);
}

std::vector<TaskTransfer> Controller::GetAllTasks() {
    return model_->GetTasks();
}

TaskActionResult Controller::SetTaskLabel(const TaskId& task_id, const std::string& label) {
    return model_->SetTaskLabel(task_id, label);
}

TaskManagerPersistence::SaveLoadStatus Controller::SaveToFile(const std::string& file_name) {
    auto model_state = model_->GetModelState();
    TaskManagerPersistence::TaskManagerParameters parameters_to_save { model_state.first, model_state.second };
    return tm_persistence_->SaveToFile(file_name, parameters_to_save);
}

TaskManagerPersistence::SaveLoadStatus Controller::LoadFromFile(const std::string& file_name) {
    auto model_state = tm_persistence_->LoadFromFile(file_name);
    if (model_state.first != TaskManagerPersistence::SaveLoadStatus::SUCCESS) {
        return model_state.first;
    }
    std::unique_ptr<IdGenerator> new_generator;
    try {
        new_generator = std::make_unique<IdGenerator>(model_state.second.last_id_.id());
    } catch (std::invalid_argument) {
        return TaskManagerPersistence::SaveLoadStatus::INVALID_FILE_STRUCTURE;
    }
    if (model_->LoadModelState(std::move(new_generator), model_state.second.tasks_)) {
        return TaskManagerPersistence::SaveLoadStatus::SUCCESS;
    } else {
        return TaskManagerPersistence::SaveLoadStatus::INVALID_FILE_STRUCTURE;
    }
}
