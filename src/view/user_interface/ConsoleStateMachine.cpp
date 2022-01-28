//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "ConsoleStateMachine.h"

#include "states/factory/StatesFactory.h"

ConsoleStateMachine::ConsoleStateMachine(const StateType initial_state,
                                         const std::shared_ptr<StateContext>& context,
                                         const std::shared_ptr<StatesFactory>& states_factory) :
                                         initial_state_(initial_state),
                                         context_(context),
                                         states_factory_(states_factory) {}

std::shared_ptr<StateContext> ConsoleStateMachine::Run() {
    std::shared_ptr<State> current_state = states_factory_->GetState(initial_state_);
    while (current_state) {
        current_state = states_factory_->GetState(current_state->Execute(*context_));
    }
    return context_;
}
