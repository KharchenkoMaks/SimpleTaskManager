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

/**
 * @brief Class for sequential executing of \b States starting from initial
 * @author Maksym Kharchenko
 */
class ConsoleStateMachine {
public:
    ConsoleStateMachine(StateType initial_state,
                        std::unique_ptr<StateContext> context,
                        const std::shared_ptr<StatesFactory>& states_factory);
public:
    /**
     * @return \b StateContext filled by States
     * @details Initial \b state and \b context are not changed after running the machine,
     * so next runs don't depend on previous ones
     */
    virtual std::unique_ptr<StateContext> Run();
public:
    virtual ~ConsoleStateMachine() = default;
private:
    StateType initial_state_;
    std::unique_ptr<StateContext> context_;
    std::shared_ptr<StatesFactory> states_factory_;
};


#endif //SIMPLETASKMANAGER_CONSOLESTATEMACHINE_H
