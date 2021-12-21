//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/AddTaskState.h"
#include "console_io/ConsoleUtilities.h"

std::shared_ptr<StateInterface> AddTaskState::Execute(StateContext& context) {
    auto state_machine = factory_.lock()->CreateStateMachine();
    std::shared_ptr<StateContext> context_with_added_task = state_machine->Run(std::make_shared<StateContext>(),
                    factory_.lock()->GetNextState(*this, StatesFactory::MoveType::NEXT));

    if (context_with_added_task->GetTask().has_value()) {
        Task task_to_add = context_with_added_task->GetTask().value();
        context.AddTaskTitle(task_to_add.title());
        context.AddTaskPriority(task_to_add.priority());
        context.AddTaskDueTime(task_to_add.due_date());
        context.SetCommand(factory_.lock()->GetCommandFactory()->CreateAddTaskCommand(context));
        return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::PREVIOUS);
    } else {
        return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::ERROR);
    }

    if (context_with_added_task->GetTask().has_value()) {

    }
    factory_.lock()->GetConsolePrinter()->WriteError("Task wasn't saved.");
    return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::ERROR);
}

AddTaskState::AddTaskState(const std::shared_ptr<StatesFactory>& factory) :
                           factory_(factory) {

}

void AddTaskState::ShowAddedTaskId(const TaskId& task_id) {
    factory_.lock()->GetConsolePrinter()->WriteLine("Task was successfully added. Task id: " + std::to_string(task_id.id()));
}
