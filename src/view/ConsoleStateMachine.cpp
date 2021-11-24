//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "ConsoleStateMachine.h"

void ConsoleStateMachine::Run(const WizardStatesFactory::States initial_state) {
    std::shared_ptr<WizardStatesFactory> states_factory = std::make_shared<WizardStatesFactory>();
    context_ = std::make_shared<WizardContext>();
    state_ = states_factory->GetState(initial_state);
    while (!context_->IsStateMachineStopped()){
        std::shared_ptr<IWizardState> next_state = state_->Execute(context_, states_factory);
        state_ = next_state;
    }
}
