//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_CONSOLESTATEMACHINE_H
#define SIMPLETASKMANAGER_CONSOLESTATEMACHINE_H

#include "StateContext.h"
#include "states/State.h"

#include <memory>
#include <optional>

class ConsoleStateMachine {
public:
    ConsoleStateMachine(const std::shared_ptr<State>& initial_state,
                        const std::shared_ptr<StateContext>& context);
public:
    virtual std::shared_ptr<StateContext> Run();
public:
    virtual ~ConsoleStateMachine() = default;
private:
    std::shared_ptr<State> initial_state_;
    std::shared_ptr<StateContext> context_;
};


#endif //SIMPLETASKMANAGER_CONSOLESTATEMACHINE_H
