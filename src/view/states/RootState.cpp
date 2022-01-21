//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "RootState.h"
#include "user_interface/console_io/ConsoleUtilities.h"

RootState::RootState(const std::shared_ptr<StatesFactory>& factory) :
                    factory_(factory) {

}

std::shared_ptr<State> RootState::Execute(StateContext& context) {
    std::string command = console_io::util::GetUserInput("", *factory_->GetConsolePrinter(), *factory_->GetConsoleReader());
    std::shared_ptr<State> next_state = factory_->GetStateByCommand(command);
    if (next_state) {
        return next_state;
    } else {
        factory_->GetConsolePrinter()->WriteError("Unknown command! Use help.");
        return factory_->GetNextState(*this, StatesFactory::MoveType::ERROR);
    }
}
