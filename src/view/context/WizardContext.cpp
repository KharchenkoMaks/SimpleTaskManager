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

Task WizardContext::CreateDefaultTask() {
    return Task::Create("default_title", Task::Priority::NONE, 0);
}

void WizardContext::AddedTaskInitialize() {
    if (!added_task_.has_value()){
        added_task_ = CreateDefaultTask();
    }
}
