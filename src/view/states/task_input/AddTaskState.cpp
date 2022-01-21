//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/AddTaskState.h"
#include "user_interface/console_io/ConsoleUtilities.h"

std::shared_ptr<State> AddTaskState::Execute(StateContext& context) {
    auto state_machine = factory_->CreateStateMachine(factory_->GetNextState(*this, StatesFactory::MoveType::NEXT),
                                                             std::make_shared<StateContext>());
    std::shared_ptr<StateContext> context_with_added_task = state_machine->Run();

    Task task_to_add = context_with_added_task->GetTaskBuilder().BuildTask();
    context.AddTaskTitle(task_to_add.title());
    context.AddTaskPriority(task_to_add.priority());
    context.AddTaskDueTime(task_to_add.due_date());
    context.AddTaskLabel(task_to_add.label());
    context.SetCommand(factory_->GetCommandFactory()->CreateAddTaskCommand(context));
    return factory_->GetNextState(*this, StatesFactory::MoveType::PREVIOUS);
}

AddTaskState::AddTaskState(const std::shared_ptr<StatesFactory>& factory) :
                           factory_(factory) {

}
