//
// Created by Maksym Kharchenko on 23.12.2021.
//

#include "UserInterface.h"

UserInterface::UserInterface(const std::shared_ptr<StatesFactory>& states_factory) :
                             states_factory_(states_factory) {

}

std::shared_ptr<CommandInterface> UserInterface::AskUserForAction() {
    auto state_machine = states_factory_->CreateStateMachine();
    std::shared_ptr<StateContext> result_context =
            state_machine->Run(std::make_shared<StateContext>(), states_factory_->GetInitialState());

    return result_context->GetCommand();
}
