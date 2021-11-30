//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "WizardStatesFactory.h"

WizardStatesFactory::WizardStatesFactory(const std::shared_ptr<Controller>& controller) : controller_(controller) {

}

std::shared_ptr<WizardStateConsole> WizardStatesFactory::GetStateByCommand(const std::string &command) {
    if (command == "add") {
        return GetLazyStateByStatesEnum(States::kAddTask);
    } else if (command == "edit") {
        return GetLazyStateByStatesEnum(States::kEditTask);
    } else if (command == "delete") {
        // delete state
        throw std::invalid_argument("Wrong command was given.");
    } else if (command == "complete") {
        // complete state
        throw std::invalid_argument("Wrong command was given.");
    } else if (command == "show") {
        // show state
        return GetLazyStateByStatesEnum(States::kShow);
    } else if (command == "help") {
        return GetLazyStateByStatesEnum(States::kHelp);
    } else if (command == "quit") {
        return GetLazyStateByStatesEnum(States::kQuit);
    } else {
        throw std::invalid_argument("Wrong command was given.");
    }
}

std::shared_ptr<WizardStateConsole> WizardStatesFactory::GetInitialState() {
    return GetLazyStateByStatesEnum(States::kRoot);
}

std::optional<std::shared_ptr<WizardStateConsole>> WizardStatesFactory::GetNextState(const QuitState& state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::PREVIOUS: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
        case MoveType::ERROR: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
        case MoveType::NEXT: {
            return std::nullopt;
        }
    }
}

std::optional<std::shared_ptr<WizardStateConsole>> WizardStatesFactory::GetNextState(const AddTaskState &state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::PREVIOUS: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
        case MoveType::ERROR: {
            return GetLazyStateByStatesEnum(States::kAddTask);
        }
        case MoveType::NEXT: {
            return GetLazyStateByStatesEnum(States::kInputTaskTitle);
        }
    }
}

std::optional<std::shared_ptr<WizardStateConsole>> WizardStatesFactory::GetNextState(const EditTaskState &state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::PREVIOUS: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
        case MoveType::ERROR: {
            return GetLazyStateByStatesEnum(States::kEditTask);
        }
        case MoveType::NEXT: {
            return GetLazyStateByStatesEnum(States::kInputTaskTitle);
        }
    }
}

std::optional<std::shared_ptr<WizardStateConsole>> WizardStatesFactory::GetNextState(const InputTaskTitleState &state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::PREVIOUS: {
            throw std::invalid_argument("No previous state for given state.");
        }
        case MoveType::ERROR: {
            return GetLazyStateByStatesEnum(States::kInputTaskTitle);
        }
        case MoveType::NEXT: {
            return GetLazyStateByStatesEnum(States::kInputTaskPriority);
        }
    };
}

std::optional<std::shared_ptr<WizardStateConsole>> WizardStatesFactory::GetNextState(const InputTaskPriorityState &state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::PREVIOUS: {
            return GetLazyStateByStatesEnum(States::kInputTaskTitle);
        }
        case MoveType::ERROR: {
            return GetLazyStateByStatesEnum(States::kInputTaskPriority);
        }
        case MoveType::NEXT: {
            return GetLazyStateByStatesEnum(States::kInputTaskDueDate);
        }
    }
}

std::optional<std::shared_ptr<WizardStateConsole>> WizardStatesFactory::GetNextState(const InputTaskDueDateState &state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::PREVIOUS: {
            return GetLazyStateByStatesEnum(States::kInputTaskPriority);
        }
        case MoveType::ERROR: {
            return GetLazyStateByStatesEnum(States::kInputTaskDueDate);
        }
        case MoveType::NEXT: {
            return std::nullopt;
        }
    }
}

std::optional<std::shared_ptr<WizardStateConsole>> WizardStatesFactory::GetNextState(const HelpState &state, const MoveType move_type) {
    switch (move_type) {
        default: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
    }
}

std::optional<std::shared_ptr<WizardStateConsole>> WizardStatesFactory::GetNextState(const RootState &state, WizardStatesFactory::MoveType move_type) {
    switch (move_type) {
        default: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
    }
}

std::optional<std::shared_ptr<WizardStateConsole>> WizardStatesFactory::GetNextState(const ShowState &state, WizardStatesFactory::MoveType move_type) {
    switch (move_type) {
        default: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
    }
}

std::shared_ptr<WizardStateConsole> WizardStatesFactory::GetLazyStateByStatesEnum(States state) {
    switch (state) {
        case States::kRoot: {
            if (!root_state_){
                root_state_ = std::make_shared<RootState>(shared_from_this(), printer_, reader_);
            }
            return root_state_;
        }
        case States::kHelp: {
            if (!help_state_){
                help_state_ = std::make_shared<HelpState>(shared_from_this(), printer_, reader_);
            }
            return help_state_;
        }
        case States::kQuit: {
            if (!quit_state_){
                quit_state_ = std::make_shared<QuitState>(shared_from_this(), printer_, reader_);
            }
            return quit_state_;
        }
        case States::kAddTask: {
            if (!add_task_state_){
                add_task_state_ = std::make_shared<AddTaskState>(controller_, shared_from_this(), printer_, reader_);
            }
            return add_task_state_;
        }
        case States::kEditTask: {
            if (!edit_task_state_){
                edit_task_state_ = std::make_shared<EditTaskState>(controller_, shared_from_this(), printer_, reader_);
            }
            return edit_task_state_;
        }
        case States::kInputTaskTitle: {
            if (!input_task_title_state_){
                input_task_title_state_ = std::make_shared<InputTaskTitleState>(shared_from_this(), printer_, reader_);
            }
            return input_task_title_state_;
        }
        case States::kInputTaskPriority: {
            if (!input_task_priority_state_){
                input_task_priority_state_ = std::make_shared<InputTaskPriorityState>(shared_from_this(), printer_, reader_);
            }
            return input_task_priority_state_;
        }
        case States::kInputTaskDueDate: {
            if (!input_task_due_date_state_){
                input_task_due_date_state_ = std::make_shared<InputTaskDueDateState>(shared_from_this(), printer_, reader_);
            }
            return input_task_due_date_state_;
        }
        case States::kShow: {
            if (!show_state_) {
                show_state_ = std::make_shared<ShowState>(controller_, shared_from_this(), printer_, reader_);
            }
            return show_state_;
        }
    }
}
