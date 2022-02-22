//
// Created by Maksym Kharchenko on 24.11.2021.
//

#ifndef SIMPLETASKMANAGER_ADDTASKSTATE_H
#define SIMPLETASKMANAGER_ADDTASKSTATE_H

#include "states/State.h"
#include "view/commands/factory/CommandFactory.h"
#include "user_interface/StateContext.h"
#include "view/user_interface/ConsoleStateMachine.h"

#include <memory>
#include <optional>

class AddTaskState : public State {
public:
    AddTaskState(StateType next_state,
                 const std::shared_ptr<CommandFactory>& command_factory,
                 std::unique_ptr<ConsoleStateMachine> state_machine);
public:
    StateType Execute(StateContext& context) override;
private:
    StateType next_state_;
    std::shared_ptr<CommandFactory> command_factory_;
    std::unique_ptr<ConsoleStateMachine> state_machine_;
};


#endif //SIMPLETASKMANAGER_ADDTASKSTATE_H
