//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "ConsoleStateMachine.h"

void ConsoleStateMachine::Run(const std::shared_ptr<WizardContext>& context,
                                                        const std::optional<std::shared_ptr<WizardStateConsole>>& initial_state) {
    state_ = initial_state;
    while (state_.has_value()){
        state_ = state_.value()->Execute(context);
    }
}
