//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "ConsoleStateMachine.h"

void ConsoleStateMachine::Run() {
    while (true){
        std::shared_ptr<IWizardState> next_state = state_->Execute(context_);
        state_ = next_state;
    }
}
