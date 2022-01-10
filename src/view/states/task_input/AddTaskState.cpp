//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/AddTaskState.h"
#include "user_interface/console_io/ConsoleUtilities.h"

std::shared_ptr<StateInterface> AddTaskState::Execute(StateContext& context) {
    auto state_machine = factory_.lock()->CreateStateMachine();
    std::shared_ptr<StateContext> context_with_added_task = state_machine->Run(std::make_shared<StateContext>(),
                    factory_.lock()->GetNextState(*this, StatesFactory::MoveType::NEXT));

    Task task_to_add = context_with_added_task->GetTaskBuilder().BuildTask();
    context.AddTaskTitle(task_to_add.title());
    context.AddTaskPriority(task_to_add.priority());
    context.AddTaskDueTime(task_to_add.due_date());
    context.AddTaskLabel(task_to_add.label());
    context.SetCommand(factory_.lock()->GetCommandFactory()->CreateAddTaskCommand(context));
    return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::PREVIOUS);
}

AddTaskState::AddTaskState(const std::shared_ptr<StatesFactory>& factory) :
                           factory_(factory) {

}
