//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "WizardStatesFactory.h"

WizardStatesFactory::WizardStatesFactory() {
    printer_ = std::make_shared<ConsolePrinter>();

    root_state_ = std::make_shared<RootState>(printer_);
    help_state_ = std::make_shared<HelpState>(printer_);
}

std::shared_ptr<RootState> WizardStatesFactory::CreateRootState() {
    return root_state_;
}

std::shared_ptr<IWizardState> WizardStatesFactory::CreateStateByCommand(const std::string &command) {
    if (command == "add") {
        // add state
    } else if (command == "edit") {
        // edit state
    } else if (command == "delete") {
        // delete state
    } else if (command == "complete") {
        // complete state
    } else if (command == "show") {
        // show state
    } else if (command == "help") {
        return help_state_;
    } else if (command == "quit") {
        // quit state
    } else {
        throw std::invalid_argument("Wrong command was given.");
    }
}
