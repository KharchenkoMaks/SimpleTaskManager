//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "ConsoleStateMachine.h"

std::shared_ptr<StateContext> ConsoleStateMachine::Run(const std::shared_ptr<StateContext>& context,
                                                        const std::shared_ptr<State>& initial_state) {
    state_ = initial_state;
    while (state_){
        state_ = state_->Execute(*context);
    }
    return context;
}
