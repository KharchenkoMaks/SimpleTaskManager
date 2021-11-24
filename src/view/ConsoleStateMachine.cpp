//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "ConsoleStateMachine.h"

void ConsoleStateMachine::Run() {
    std::shared_ptr<WizardStatesFactory> states_factory = std::make_shared<WizardStatesFactory>();
    context_ = std::make_shared<WizardContext>();
    state_ = states_factory->GetRootState();
    while (!context_->IsWizardEnded()){
        std::shared_ptr<IWizardState> next_state = state_->Execute(context_, states_factory);
        state_ = next_state;
    }
}
