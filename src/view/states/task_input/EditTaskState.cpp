//
// Created by Maksym Kharchenko on 25.11.2021.
//

#include "states/task_input/EditTaskState.h"

EditTaskState::EditTaskState(std::unique_ptr<StateDependencies> dependencies) :
                            dependencies_(std::move(dependencies)) {

}

std::shared_ptr<WizardStateInterface> EditTaskState::Execute(std::shared_ptr<WizardContext> context) {
    std::optional<TaskId> editing_task_id = dependencies_->GetTaskIdFromUser();
    if (!editing_task_id.has_value()) {
        dependencies_->GetConsolePrinter()->WriteError("Incorrect task id was given, try again!");
        return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
    }

    // Creating new context
    std::shared_ptr<WizardContext> context_task_editing = std::make_shared<WizardContext>();
    // Setting task to edit in context
    context_task_editing->SetEditingTask(editing_task_id.value(),
                                         dependencies_->GetController()->GetTask(editing_task_id.value()).value());

    context_task_editing = dependencies_->RunStateMachine(context_task_editing,
                                           dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT));

    // Giving edited task to controller
    TaskActionResult edit_task_result =
            dependencies_->GetController()->EditTask(context_task_editing->GetTaskId().value(), context_task_editing->GetTask().value());

    switch(edit_task_result) {
        case TaskActionResult::SUCCESS: {
            return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
        }
        case TaskActionResult::FAIL_NO_SUCH_TASK: {
            dependencies_->GetConsolePrinter()->WriteError("Task with such id wasn't found.");
            return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
        }
        default: {
            dependencies_->GetConsolePrinter()->WriteError("Invalid task was given, try again.");
            return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
        }
    }
}
