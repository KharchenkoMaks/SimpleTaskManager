//
// Created by Maksym Kharchenko on 29.11.2021.
//

#include "Controller.h"

Controller::Controller(std::unique_ptr<IModel> model,
                       std::unique_ptr<TaskValidator> task_validator) :
                       model_(std::move(model)),
                       task_validator_(std::move(task_validator)) {

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

std::optional<Task> Controller::GetTask(const TaskId& task_id) const {
    std::optional<TaskTransfer> task = model_->GetTask(task_id);
    if (task.has_value()){
        return task->GetTask();
    } else {
        return std::nullopt;
    }
}

std::vector<TaskTransfer> Controller::GetAllTasks() {
    return model_->GetTasks();
}

TaskActionResult Controller::SetTaskLabel(const TaskId& task_id, const std::string& label) {
    return model_->SetTaskLabel(task_id, label);
}
