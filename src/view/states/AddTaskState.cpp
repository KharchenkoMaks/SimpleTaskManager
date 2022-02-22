//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "AddTaskState.h"
#include "user_interface/console_io/ConsoleUtilities.h"

StateType AddTaskState::Execute(StateContext& context) {
    std::shared_ptr<StateContext> context_with_added_task = state_machine_->Run();

    context.SetTaskBuilder(context_with_added_task->GetTaskBuilder());
    context.SetCommand(command_factory_->CreateAddTaskCommand(context));
    return next_state_;
}

AddTaskState::AddTaskState(const StateType next_state,
                           const std::shared_ptr<CommandFactory>& command_factory,
                           std::unique_ptr<ConsoleStateMachine> state_machine) :
                           next_state_(next_state),
                           command_factory_(command_factory),
                           state_machine_(std::move(state_machine)) {}
