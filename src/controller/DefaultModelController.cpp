//
// Created by Maksym Kharchenko on 24.01.2022.
//

#include "DefaultModelController.h"

#include "logs/DefaultLogging.h"

DefaultModelController::DefaultModelController(std::unique_ptr<Model> model,
                                 std::unique_ptr<TaskValidator> task_validator,
                                 std::unique_ptr<persistence::PersistenceFactory> persistence_factory) :
        model_(std::move(model)),
        task_validator_(std::move(task_validator)),
        persistence_factory_(std::move(persistence_factory)) {

}

std::pair<ControllerRequestResult, TaskId> DefaultModelController::AddTask(const Task& task) {
    if (task_validator_->ValidateTask(task)) {
        LOG_TRIVIAL(info) << "Sending request, Task: {" << task.ShortDebugString() << "}";

        std::pair<TaskActionResult, TaskId> result = model_->AddTask(task);
        return std::make_pair(FormControllerRequestResult(result.first), result.second);
    } else {
        LOG_TRIVIAL(warning) << "Invalid task was given, Task: {" << task.ShortDebugString() << "}";
        return std::make_pair(ControllerRequestResult::FAIL_INVALID_TASK, TaskId::default_instance());
    }
}

std::pair<ControllerRequestResult, TaskId> DefaultModelController::AddSubTask(const Task& task, const TaskId& parent_id) {
    if (task_validator_->ValidateTask(task)) {
        LOG_TRIVIAL(info) << "Sending request, Task: {" << task.ShortDebugString() << "} parent id: " << parent_id.id();

        std::pair<TaskActionResult, TaskId> result = model_->AddSubTask(task, parent_id);
        return std::make_pair(FormControllerRequestResult(result.first), result.second);
    } else {
        LOG_TRIVIAL(warning) << "Invalid task was given, Task: {" << task.ShortDebugString() << "}";
        return std::make_pair(ControllerRequestResult::FAIL_INVALID_TASK, TaskId::default_instance());
    }
}

ControllerRequestResult DefaultModelController::EditTask(const TaskId& task_id, const Task& task) {
    if (task_validator_->ValidateTask(task)) {
        TaskActionResult result = model_->EditTask(task_id, task);
        return FormControllerRequestResult(result);
    }
    return ControllerRequestResult::FAIL_INVALID_TASK;
}

ControllerRequestResult DefaultModelController::DeleteTask(const TaskId& task_id) {
    TaskActionResult result = model_->DeleteTask(task_id, false);
    return FormControllerRequestResult(result);
}

ControllerRequestResult DefaultModelController::DeleteTaskWithSubTasks(const TaskId& task_id) {
    TaskActionResult result = model_->DeleteTask(task_id, true);
    return FormControllerRequestResult(result);
}

ControllerRequestResult DefaultModelController::CompleteTask(const TaskId& task_id) {
    TaskActionResult result = model_->CompleteTask(task_id, false);
    return FormControllerRequestResult(result);
}

ControllerRequestResult DefaultModelController::CompleteTaskWithSubTasks(const TaskId& task_id) {
    TaskActionResult result = model_->CompleteTask(task_id, true);
    return FormControllerRequestResult(result);
}

std::optional<RelationalTask> DefaultModelController::GetTask(const TaskId& task_id) {
    return model_->GetTask(task_id);
}

std::vector<RelationalTask> DefaultModelController::GetAllTasks() {
    auto tasks = model_->GetTasks();

    LOG_TRIVIAL(info) << "Tasks received: " << tasks.size();

    return tasks;
}

ControllerRequestResult DefaultModelController::AddTaskLabel(const TaskId& task_id, const std::string& label) {
    TaskActionResult result = model_->AddTaskLabel(task_id, label);
    return FormControllerRequestResult(result);
}

ControllerRequestResult DefaultModelController::RemoveTaskLabel(const TaskId &task_id, const std::string& label) {
    TaskActionResult result = model_->RemoveTaskLabel(task_id, label);
    return FormControllerRequestResult(result);
}

ControllerRequestResult DefaultModelController::SaveToFile(const std::string& file_name) {
    auto persistence = persistence_factory_->CreateFilePersistence(file_name);
    persistence::SaveLoadStatus result = persistence->Save(model_->GetTasks());
    return FormControllerRequestResult(result);
}

ControllerRequestResult DefaultModelController::LoadFromFile(const std::string& file_name) {
    auto persistence = persistence_factory_->CreateFilePersistence(file_name);
    auto model_state = persistence->Load();
    if (model_state.first != persistence::SaveLoadStatus::SUCCESS) {
        return FormControllerRequestResult(model_state.first);
    }
    if (model_->LoadModelState(model_state.second)) {
        return ControllerRequestResult::SUCCESS;
    } else {
        return ControllerRequestResult::FILE_DAMAGED;
    }
}

std::vector<RelationalTask> DefaultModelController::GetTasksByLabel(const std::string& task_label) {
    return model_->GetTasksByLabel(task_label);
}
