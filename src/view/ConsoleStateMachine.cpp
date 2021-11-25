//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "ConsoleStateMachine.h"

WizardContext ConsoleStateMachine::Run(const WizardStatesFactory::States initial_state) {
    std::shared_ptr<WizardStatesFactory> states_factory = std::make_shared<WizardStatesFactory>();
    context_ = std::make_shared<WizardContext>();
    state_ = states_factory->GetState(initial_state);
    while (state_.has_value()){
        state_ = state_.value()->Execute(context_, states_factory);
    }
    if (context_.unique()) {
        // Copying context and returning it
        return WizardContext(*(context_.get()));
    }
    else {
        throw std::runtime_error("Context leak in StateMachine");
    }
}
