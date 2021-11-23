//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "ConsoleStateMachine.h"

void ConsoleStateMachine::Run() {
    std::shared_ptr<WizardStatesFactory> states_factory = std::make_shared<WizardStatesFactory>();
    context_ = std::make_shared<WizardContext>(states_factory);
    state_ = states_factory->CreateRootState();
    while (true){
        std::shared_ptr<IWizardState> next_state = state_->Execute(context_);
        state_ = next_state;
    }
}
