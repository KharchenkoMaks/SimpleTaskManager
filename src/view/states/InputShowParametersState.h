//
// Created by Maksym Kharchenko on 30.11.2021.
//

#ifndef SIMPLETASKMANAGER_INPUTSHOWPARAMETERSSTATE_H
#define SIMPLETASKMANAGER_INPUTSHOWPARAMETERSSTATE_H

#include "State.h"
#include "user_interface/StateContext.h"
#include "view/commands/factory/CommandFactory.h"
#include "Task.pb.h"
#include "view/user_interface/ConsoleStateMachine.h"

#include <memory>
#include <optional>

class InputShowParametersState : public State {
public:
    InputShowParametersState(StateType next_state,
                             const std::shared_ptr<CommandFactory>& command_factory,
                             std::unique_ptr<ConsoleStateMachine> state_machine);
public:
    StateType Execute(StateContext& context) override;
private:
    StateType next_state_;
    std::shared_ptr<CommandFactory> command_factory_;
    std::unique_ptr<ConsoleStateMachine> state_machine_;
};


#endif //SIMPLETASKMANAGER_INPUTSHOWPARAMETERSSTATE_H
