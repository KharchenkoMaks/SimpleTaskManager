//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "ConsoleStateMachine.h"

ConsoleStateMachine::ConsoleStateMachine(const std::shared_ptr<State>& initial_state,
                                         const std::shared_ptr<StateContext>& context) :
                                         initial_state_(initial_state),
                                         context_(context) {

}

std::shared_ptr<StateContext> ConsoleStateMachine::Run() {
    std::shared_ptr<State> current_state = initial_state_;
    while (current_state){
        current_state = current_state->Execute(*context_);
    }
    return context_;
}
