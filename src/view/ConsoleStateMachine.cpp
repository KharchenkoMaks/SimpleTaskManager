//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "ConsoleStateMachine.h"

void ConsoleStateMachine::Run() {
    while (state_.has_value()){
        state_ = state_.value()->Execute(context_);
    }
}

ConsoleStateMachine::ConsoleStateMachine(const std::shared_ptr<WizardContext>& context,
                                         const std::optional<std::shared_ptr<IWizardState>>& initial_state) :
                                         context_(context),
                                         state_(initial_state) {

}
