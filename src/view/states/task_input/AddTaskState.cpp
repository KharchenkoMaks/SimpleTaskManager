//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/AddTaskState.h"
#include "user_interface/console_io/ConsoleUtilities.h"

std::shared_ptr<State> AddTaskState::Execute(StateContext& context) {
    auto state_machine = factory_.lock()->CreateStateMachine(factory_.lock()->GetNextState(*this, StatesFactory::MoveType::NEXT),
                                                             std::make_shared<StateContext>());
    std::shared_ptr<StateContext> context_with_added_task = state_machine->Run();

    context.SetTaskBuilder(context_with_added_task->GetTaskBuilder());
    context.SetCommand(factory_.lock()->GetCommandFactory()->CreateAddTaskCommand(context));
    return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::PREVIOUS);
}

AddTaskState::AddTaskState(const std::shared_ptr<StatesFactory>& factory) :
                           factory_(factory) {

}
