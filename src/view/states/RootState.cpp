//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "RootState.h"
#include "console_io/ConsoleUtilities.h"

RootState::RootState(const std::shared_ptr<WizardStatesFactory>& factory) :
                    factory_(factory) {

}

std::shared_ptr<WizardStateInterface> RootState::Execute(std::shared_ptr<WizardContext> context) {
    std::string command = console_io::util::GetUserInput("", *factory_.lock()->GetConsolePrinter(), *factory_.lock()->GetConsoleReader());
    std::shared_ptr<WizardStateInterface> next_state =
            factory_.lock()->GetStateByCommand(command);
    if (next_state) {
        return next_state;
    } else {
        factory_.lock()->GetConsolePrinter()->WriteError("Unknown command! Use help.");
        return factory_.lock()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
    }
}
