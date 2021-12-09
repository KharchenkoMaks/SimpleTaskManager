//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "RootState.h"

RootState::RootState(const std::shared_ptr<WizardStatesFactory>& states_factory,
                     const std::shared_ptr<ConsolePrinter>& printer,
                     const std::shared_ptr<ConsoleReader>& reader) :
                     WizardStateConsole(states_factory, printer, reader) {

}

std::shared_ptr<WizardStateConsole> RootState::Execute(std::shared_ptr<WizardContext> context) {
    std::string command = GetUserInput("");
    std::shared_ptr<WizardStateConsole> next_state =
            GetStatesFactory()->GetStateByCommand(command);
    if (next_state) {
        return next_state;
    } else {
        GetConsolePrinter()->WriteError("Unknown command! Use help.");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
    }
}
