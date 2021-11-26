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
    GetConsolePrinter()->Write("> ");
    std::string command = GetConsoleReader()->ReadLine();
    try {
        std::shared_ptr<IWizardState> next_state =
                state_factory->GetStateByCommand(command);
        return next_state;
    } catch (std::invalid_argument){
        GetConsolePrinter()->WriteError("Unknown command! Use help.");
        return state_factory->GetState(WizardStatesFactory::States::kRoot);
    }
}
