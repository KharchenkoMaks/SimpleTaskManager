//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "ConsoleStateMachine.h"

#include "states/factory/StatesFactory.h"

ConsoleStateMachine::ConsoleStateMachine(const StateType initial_state,
                                         std::unique_ptr<StateContext> context,
                                         const std::shared_ptr<StatesFactory>& states_factory) :
                                         initial_state_(initial_state),
                                         context_(std::move(context)),
                                         states_factory_(states_factory) {}

std::unique_ptr<StateContext> ConsoleStateMachine::Run() {
    // Saving machine's initial state and context to run it for several times
    std::shared_ptr<State> current_state = states_factory_->GetState(initial_state_);
    auto current_context = std::make_unique<StateContext>(*context_);
    while (current_state) {
        current_state = states_factory_->GetState(current_state->Execute(*current_context));
    }
    return std::move(current_context);
}
