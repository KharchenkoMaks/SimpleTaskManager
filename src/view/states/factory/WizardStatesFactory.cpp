//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "WizardStatesFactory.h"

WizardStatesFactory::WizardStatesFactory() {
    root_state_ = std::make_shared<RootState>(ConsolePrinter::Create());
    help_state_ = std::make_shared<HelpState>(ConsolePrinter::Create());
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
        // help state
    } else if (command == "quit") {
        // quit state
    } else {
        throw std::invalid_argument("Wrong command was given.");
    }
}
