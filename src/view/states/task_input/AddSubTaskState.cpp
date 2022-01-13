//
// Created by Maksym Kharchenko on 02.12.2021.
//

#include "AddSubTaskState.h"
#include "user_interface/console_io/ConsoleUtilities.h"

AddSubTaskState::AddSubTaskState(const std::shared_ptr<StatesFactory>& factory) : factory_(factory) {

}

std::shared_ptr<State> AddSubTaskState::Execute(StateContext& context) {
    std::optional<TaskId> parent_task_id = console_io::util::GetTaskIdFromUser("Parent Task ID", *factory_.lock()->GetConsolePrinter(), *factory_.lock()->GetConsoleReader());
    if (!parent_task_id.has_value()) {
        factory_.lock()->GetConsolePrinter()->WriteError("Incorrect task id was given, try again!");
        return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::ERROR);
    }

    auto state_machine = factory_.lock()->CreateStateMachine();

    std::shared_ptr<StateContext> context_with_added_task =
            state_machine->Run(std::make_shared<StateContext>(),
                                           factory_.lock()->GetNextState(*this,StatesFactory::MoveType::NEXT));

    Task task_to_add = context_with_added_task->GetTaskBuilder().BuildTask();
    context.AddTaskTitle(task_to_add.title());
    context.AddTaskPriority(task_to_add.priority());
    context.AddTaskDueTime(task_to_add.due_date());
    context.AddTaskLabel(task_to_add.label());
    context.SetTaskId(parent_task_id.value());
    context.SetCommand(factory_.lock()->GetCommandFactory()->CreateAddSubTaskCommand(context));
    return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::PREVIOUS);
}
