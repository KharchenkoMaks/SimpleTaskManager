//
// Created by Maksym Kharchenko on 09.12.2021.
//

#include "EndState.h"

EndState::EndState(const std::shared_ptr<WizardStatesFactory> &states_factory,
                   const std::shared_ptr<ConsolePrinter> &printer, const std::shared_ptr<ConsoleReader> &reader)
        : WizardStateConsole(states_factory, printer, reader) {

}

std::shared_ptr<WizardStateConsole> EndState::Execute(std::shared_ptr<WizardContext> context) {
    return nullptr;
}
