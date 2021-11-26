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

std::shared_ptr<IWizardState> WizardStatesFactory::GetState(const WizardStatesFactory::States state) {
    switch (state){
        case States::kRoot: {
            return root_state_;
        }
        case States::kHelp: {
            return help_state_;
        }
        case States::kQuit: {
            return quit_state_;
        }
        case States::kAddTask: {
            return add_task_state_;
        }
        case States::kEditTask: {
            return edit_task_state_;
        }
        case States::kInputTaskTitle: {
            return input_task_title_state_;
        }
        case States::kInputTaskPriority: {
            return input_task_priority_state_;
        }
        case States::kInputTaskDueDate: {
            return input_task_due_date_state_;
        }
    }
}
