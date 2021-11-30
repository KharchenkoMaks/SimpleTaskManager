//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "ConsoleStateMachine.h"

std::shared_ptr<WizardContext> ConsoleStateMachine::Run() {
    while (state_.has_value()){
        state_ = state_.value()->Execute(context_);
    }
    return context_;
}

ConsoleStateMachine::ConsoleStateMachine(const std::shared_ptr<WizardContext>& context,
                                         const std::optional<std::shared_ptr<WizardStateConsole>>& initial_state) :
                                         state_(initial_state),
                                         context_(context) {

}
