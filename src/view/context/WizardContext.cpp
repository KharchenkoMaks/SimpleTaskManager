//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "context/WizardContext.h"

WizardContext::WizardContext() {
    state_machine_stopped_ = false;

    confirm_message_ = std::nullopt;
    confirmation_ = ConfirmationStatus::kNone;

    added_task_ = std::nullopt;
}

// QuitState

void WizardContext::InterruptStateMachine() {
    state_machine_stopped_ = true;
}

bool WizardContext::IsStateMachineStopped() {
    return state_machine_stopped_;
}

// ConfirmState

void WizardContext::SetConfirmMessage(const std::string& message) {
    confirm_message_ = message;
}

void WizardContext::ResetConfirmMessage() {
    confirm_message_ = std::nullopt;
}

std::optional<std::string> WizardContext::GetConfirmMessage() {
    return confirm_message_;
}

void WizardContext::ConfirmAction() {
    confirmation_ = ConfirmationStatus::kConfirmed;
}

void WizardContext::NotConfirmAction() {
    confirmation_ = ConfirmationStatus::kNotConfirmed;
}

void WizardContext::ResetActionConfirmation() {
    confirmation_ = ConfirmationStatus::kNone;
}

WizardContext::ConfirmationStatus WizardContext::GetConfirmationStatus() {
    return confirmation_;
}

std::optional<Task> WizardContext::GetAddedTask() {
    return added_task_;
}

void WizardContext::ResetAddedTask() {
    added_task_ = std::nullopt;
}

void WizardContext::AddTaskTitle(const std::string &title) {
    AddedTaskInitialize();
    added_task_ = Task::Create(title,
                               added_task_->GetPriority(),
                               added_task_->GetDueTime(),
                               added_task_->IsCompleted(),
                               added_task_->GetLabel());
}

void WizardContext::AddTaskPriority(const Task::Priority priority) {
    AddedTaskInitialize();
    added_task_ = Task::Create(added_task_->GetTitle(),
                               priority,
                               added_task_->GetDueTime(),
                               added_task_->IsCompleted(),
                               added_task_->GetLabel());
}

void WizardContext::AddTaskDueTime(time_t due_time) {
    AddedTaskInitialize();
    added_task_ = Task::Create(added_task_->GetTitle(),
                               added_task_->GetPriority(),
                               due_time,
                               added_task_->IsCompleted(),
                               added_task_->GetLabel());
}

void WizardContext::AddTask(const std::optional<Task>& task) {
    if (task.has_value()) {
        added_task_ = task;
    } else {
        throw std::invalid_argument("Task was empty");
    }
}

Task WizardContext::CreateDefaultTask() {
    return Task::Create("default_title", Task::Priority::NONE, 0);
}

void WizardContext::AddedTaskInitialize() {
    if (!added_task_.has_value()){
        added_task_ = CreateDefaultTask();
    }
}

void WizardContext::SetEditingTaskId(const TaskId& task_id) {
    editing_task_id_ = task_id;
}

void WizardContext::SetEditingTaskId(const std::string& task_id) {
    editing_task_id_ = TaskId::Create(task_id);
}

std::optional<TaskId> WizardContext::GetEditingTaskId() {
    return editing_task_id_;
}

void WizardContext::ResetEditingTaskId() {
    editing_task_id_ = std::nullopt;
}
