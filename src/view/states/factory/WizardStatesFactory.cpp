//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "WizardStatesFactory.h"

WizardStatesFactory::WizardStatesFactory() {
    printer_ = std::make_shared<ConsolePrinter>();

    // Using printer
    root_state_ = std::make_shared<RootState>(printer_);
    help_state_ = std::make_shared<HelpState>(printer_);

    // Not using printer
    quit_state_ = std::make_shared<QuitState>();
}

std::shared_ptr<RootState> WizardStatesFactory::CreateRootState() {
    return root_state_;
}

std::shared_ptr<IWizardState> WizardStatesFactory::CreateStateByCommand(const std::string &command) {
    if (command == "add") {
        // add state
        throw std::invalid_argument("Wrong command was given.");
    } else if (command == "edit") {
        // edit state
        throw std::invalid_argument("Wrong command was given.");
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
