//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "WizardStatesFactory.h"

WizardStatesFactory::WizardStatesFactory() {
    printer_ = std::make_shared<ConsolePrinter>();
    reader_ = std::make_shared<ConsoleReader>();

    // Using printer
    root_state_ = std::make_shared<RootState>(printer_, reader_);
    help_state_ = std::make_shared<HelpState>(printer_, reader_);
    quit_state_ = std::make_shared<QuitState>(printer_, reader_);

    edit_task_state_ = std::make_shared<EditTaskState>(printer_, reader_);

    input_task_title_state_ = std::make_shared<InputTaskTitleState>(printer_, reader_);
    input_task_priority_state_ = std::make_shared<InputTaskPriorityState>(printer_, reader_);
    input_task_due_date_state_ = std::make_shared<InputTaskDueDateState>(printer_, reader_);

    // Not using printer
    add_task_state_ = std::make_shared<AddTaskState>();
}

std::shared_ptr<IWizardState> WizardStatesFactory::GetStateByCommand(const std::string &command) {
    if (command == "add") {
        return add_task_state_;
    } else if (command == "edit") {
        return edit_task_state_;
    } else if (command == "delete") {
        // delete state
        throw std::invalid_argument("Wrong command was given.");
    } else if (command == "complete") {
        // complete state
        throw std::invalid_argument("Wrong command was given.");
    } else if (command == "show") {
        // show state
        throw std::invalid_argument("Wrong command was given.");
    } else if (command == "help") {
        return help_state_;
    } else if (command == "quit") {
        return quit_state_;
    } else {
        throw std::invalid_argument("Wrong command was given.");
    }
}

std::shared_ptr<IWizardState> WizardStatesFactory::GetInitialState() {
    return root_state_;
}

std::optional<std::shared_ptr<IWizardState>> WizardStatesFactory::GetPreviousState(const HelpState &state) {
    return root_state_;
}

std::optional<std::shared_ptr<IWizardState>> WizardStatesFactory::GetPreviousState(const QuitState &state) {
    return root_state_;
}

std::optional<std::shared_ptr<IWizardState>> WizardStatesFactory::GetPreviousState(const RootState& state) {
    return root_state_;
}

std::optional<std::shared_ptr<IWizardState>> WizardStatesFactory::GetPreviousState(const AddTaskState &state) {
    return root_state_
}

std::optional<std::shared_ptr<IWizardState>> WizardStatesFactory::GetPreviousState(const EditTaskState &state) {
    return root_state_;
}

std::optional<std::shared_ptr<IWizardState>> WizardStatesFactory::GetPreviousState(const InputTaskTitleState &state) {
    return input_task_title_state_;
}

std::optional<std::shared_ptr<IWizardState>> WizardStatesFactory::GetPreviousState(const InputTaskPriorityState &state) {
    return input_task_priority_state_;
}

std::optional<std::shared_ptr<IWizardState>> WizardStatesFactory::GetPreviousState(const InputTaskDueDateState &state) {
    return input_task_due_date_state_;
}

std::optional<std::shared_ptr<IWizardState>> WizardStatesFactory::GetNextState(const QuitState& state) {
    return std::nullopt;
}

std::optional<std::shared_ptr<IWizardState>> WizardStatesFactory::GetNextState(const AddTaskState &state) {
    return input_task_title_state_;
}

std::optional<std::shared_ptr<IWizardState>> WizardStatesFactory::GetNextState(const EditTaskState &state) {
    return input_task_title_state_;
}

std::optional<std::shared_ptr<IWizardState>> WizardStatesFactory::GetNextState(const InputTaskTitleState &state) {
    return input_task_priority_state_;
}

std::optional<std::shared_ptr<IWizardState>> WizardStatesFactory::GetNextState(const InputTaskPriorityState &state) {
    return input_task_due_date_state_;
}

std::optional<std::shared_ptr<IWizardState>> WizardStatesFactory::GetNextState(const InputTaskDueDateState &state) {
    return std::nullopt;
}

