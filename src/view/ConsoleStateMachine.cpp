//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "ConsoleStateMachine.h"

std::shared_ptr<WizardContext> ConsoleStateMachine::Run(const std::shared_ptr<WizardContext>& context,
                                                        const std::shared_ptr<WizardStateConsole>& initial_state) {
    state_ = initial_state;
    while (state_){
        state_ = state_->Execute(context);
    }
    return context;
}
