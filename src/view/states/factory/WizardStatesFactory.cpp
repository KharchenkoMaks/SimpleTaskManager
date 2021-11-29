//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "WizardStatesFactory.h"

WizardStatesFactory::WizardStatesFactory() {
    printer_ = std::make_shared<ConsolePrinter>();
    reader_ = std::make_shared<ConsoleReader>();

    // Using printer
    root_state_ = std::make_shared<RootState>(shared_from_this(), printer_, reader_);
    help_state_ = std::make_shared<HelpState>(shared_from_this(), printer_, reader_);
    quit_state_ = std::make_shared<QuitState>(shared_from_this(), printer_, reader_);

    edit_task_state_ = std::make_shared<EditTaskState>(shared_from_this(), printer_, reader_);

    input_task_title_state_ = std::make_shared<InputTaskTitleState>(shared_from_this(), printer_, reader_);
    input_task_priority_state_ = std::make_shared<InputTaskPriorityState>(shared_from_this(), printer_, reader_);
    input_task_due_date_state_ = std::make_shared<InputTaskDueDateState>(shared_from_this(), printer_, reader_);

    // Not using printer
    add_task_state_ = std::make_shared<AddTaskState>(shared_from_this());
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

std::optional<std::shared_ptr<IWizardState>> WizardStatesFactory::GetNextState(const QuitState& state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::PREVIOUS: {
            return root_state_;
        }
        case MoveType::ERROR: {
            return root_state_;
        }
        case MoveType::NEXT: {
            return std::nullopt;
        }
    }
}

std::optional<std::shared_ptr<IWizardState>> WizardStatesFactory::GetNextState(const AddTaskState &state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::PREVIOUS: {
            return root_state_;
        }
        case MoveType::ERROR: {
            return add_task_state_;
        }
        case MoveType::NEXT: {
            return input_task_title_state_;
        }
    }
}

std::optional<std::shared_ptr<IWizardState>> WizardStatesFactory::GetNextState(const EditTaskState &state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::PREVIOUS: {
            return root_state_;
        }
        case MoveType::ERROR: {
            return edit_task_state_;
        }
        case MoveType::NEXT: {
            return input_task_title_state_;
        }
    }
}

std::optional<std::shared_ptr<IWizardState>> WizardStatesFactory::GetNextState(const InputTaskTitleState &state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::PREVIOUS: {
            throw std::invalid_argument("No previous state for given state.");
        }
        case MoveType::ERROR: {
            return input_task_title_state_;
        }
        case MoveType::NEXT: {
            return input_task_priority_state_;
        }
    };
}

std::optional<std::shared_ptr<IWizardState>> WizardStatesFactory::GetNextState(const InputTaskPriorityState &state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::PREVIOUS: {
            return input_task_title_state_;
        }
        case MoveType::ERROR: {
            return input_task_priority_state_;
        }
        case MoveType::NEXT: {
            return input_task_due_date_state_;
        }
    }
}

std::optional<std::shared_ptr<IWizardState>> WizardStatesFactory::GetNextState(const InputTaskDueDateState &state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::PREVIOUS: {
            return input_task_priority_state_;
        }
        case MoveType::ERROR: {
            return input_task_due_date_state_;
        }
        case MoveType::NEXT: {
            return std::nullopt;
        }
    }
}

std::optional<std::shared_ptr<IWizardState>> WizardStatesFactory::GetNextState(const HelpState &state, const MoveType move_type) {
    switch (move_type) {
        default: {
            return root_state_;
        }
    }
}

std::optional<std::shared_ptr<IWizardState>> WizardStatesFactory::GetNextState(const RootState &state, WizardStatesFactory::MoveType move_type) {
    switch (move_type) {
        default: {
            return root_state_;
        }
    }
}

