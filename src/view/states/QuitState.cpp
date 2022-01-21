//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "QuitState.h"
#include "user_interface/console_io/ConsoleUtilities.h"

std::shared_ptr<State> QuitState::Execute(StateContext& context) {
    if (console_io::util::UserConfirm("Are you sure?", *factory_->GetConsolePrinter(), *factory_->GetConsoleReader())) {
        return factory_->GetNextState(*this, StatesFactory::MoveType::NEXT);
    } else {
        return factory_->GetNextState(*this, StatesFactory::MoveType::PREVIOUS);
    }
}

QuitState::QuitState(const std::shared_ptr<StatesFactory>& factory) :
                    factory_(factory) {

}
