//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_CONSOLESTATEMACHINE_H
#define SIMPLETASKMANAGER_CONSOLESTATEMACHINE_H

#include "StateContext.h"
#include "states/StateInterface.h"

#include <memory>
#include <optional>

class ConsoleStateMachine {
public:
    virtual std::shared_ptr<StateContext> Run(const std::shared_ptr<StateContext>& context,
                                               const std::shared_ptr<StateInterface>& initial_state);
public:
    virtual ~ConsoleStateMachine() = default;
private:
    std::shared_ptr<StateInterface> state_;
};


#endif //SIMPLETASKMANAGER_CONSOLESTATEMACHINE_H
