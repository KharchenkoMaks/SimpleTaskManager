//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "ConsoleStateMachine.h"

ConsoleStateMachine::ConsoleStateMachine(const std::shared_ptr<State>& initial_state,
                                         const std::shared_ptr<StateContext>& context) :
                                         state_(initial_state),
                                         context_(context) {

}

std::shared_ptr<StateContext> ConsoleStateMachine::Run() {
    while (state_){
        state_ = state_->Execute(*context_);
    }
    return context_;
}
