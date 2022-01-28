//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_CONSOLESTATEMACHINE_H
#define SIMPLETASKMANAGER_CONSOLESTATEMACHINE_H

#include "StateContext.h"
#include "states/State.h"

#include <memory>
#include <optional>

class StatesFactory;

class ConsoleStateMachine {
public:
    ConsoleStateMachine(StateType initial_state,
                        const std::shared_ptr<StateContext>& context,
                        const std::shared_ptr<StatesFactory>& states_factory);
public:
    virtual std::shared_ptr<StateContext> Run();
public:
    virtual ~ConsoleStateMachine() = default;
private:
    StateType initial_state_;
    std::shared_ptr<StateContext> context_;
    std::shared_ptr<StatesFactory> states_factory_;
};


#endif //SIMPLETASKMANAGER_CONSOLESTATEMACHINE_H
