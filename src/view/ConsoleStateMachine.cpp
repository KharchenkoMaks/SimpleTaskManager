//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "ConsoleStateMachine.h"

void ConsoleStateMachine::Run(const WizardStatesFactory::States initial_state,
                              std::shared_ptr<WizardContext> context,
                              std::shared_ptr<WizardStatesFactory> states_factory) {
    context_ = context;
    state_ = states_factory->GetState(initial_state);
    while (state_.has_value()){
        state_ = state_.value()->Execute(context_, states_factory);
    }
}
