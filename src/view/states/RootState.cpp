//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "RootState.h"

RootState::RootState(const std::shared_ptr<ConsolePrinter>& printer,
                     const std::shared_ptr<ConsoleReader>& reader) :
                     WizardStateConsole(printer, reader) {

}

std::optional<std::shared_ptr<IWizardState>> RootState::Execute(std::shared_ptr<WizardContext> context,
                                                 std::shared_ptr<WizardStatesFactory> state_factory) {
    std::string command = GetUserInput("");
    try {
        return state_factory->GetStateByCommand(command);;
    } catch (std::invalid_argument){
        GetConsolePrinter()->WriteError("Unknown command! Use help.");
        return state_factory->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
    }
}
