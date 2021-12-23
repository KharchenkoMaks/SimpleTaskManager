//
// Created by Maksym Kharchenko on 25.11.2021.
//

#include "states/task_input/EditTaskState.h"
#include "user_interface/console_io/ConsoleUtilities.h"

EditTaskState::EditTaskState(const std::shared_ptr<StatesFactory>& factory) :
                            factory_(factory) {

}

std::shared_ptr<StateInterface> EditTaskState::Execute(std::shared_ptr<StateContext> context) {
    std::optional<TaskId> editing_task_id = console_io::util::GetTaskIdFromUser("Task ID", *factory_.lock()->GetConsolePrinter(), *factory_.lock()->GetConsoleReader());
    if (!editing_task_id.has_value()) {
        factory_.lock()->GetConsolePrinter()->WriteError("Incorrect task id was given, try again!");
        return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::ERROR);
    }

    // Creating new context
    std::shared_ptr<StateContext> context_task_editing = std::make_shared<StateContext>();
    // Setting task to edit in context
    std::optional<TaskTransfer> task_to_edit = factory_.lock()->GetController()->GetTask(editing_task_id.value());
    if (!task_to_edit.has_value()) {
        factory_.lock()->GetConsolePrinter()->WriteError("Task with such id wasn't found.");
        return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::ERROR);
    }
    context_task_editing->SetEditingTask(editing_task_id.value(), task_to_edit.value().task());

    auto state_machine = factory_.lock()->CreateStateMachine();
    context_task_editing = state_machine->Run(context_task_editing,
                                           factory_.lock()->GetNextState(*this, StatesFactory::MoveType::NEXT));

    // Giving edited task to controller
    TaskActionResult edit_task_result =
            factory_.lock()->GetController()->EditTask(context_task_editing->GetTaskId().value(), context_task_editing->GetTask().value());

    switch(edit_task_result) {
        case TaskActionResult::SUCCESS: {
            return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::PREVIOUS);
        }
        default: {
            factory_.lock()->GetConsolePrinter()->WriteError("Invalid task was given, try again.");
            return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::ERROR);
        }
    }
}
