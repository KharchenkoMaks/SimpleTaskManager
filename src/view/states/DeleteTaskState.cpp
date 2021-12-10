//
// Created by Maksym Kharchenko on 02.12.2021.
//

#include "DeleteTaskState.h"

DeleteTaskState::DeleteTaskState(std::unique_ptr<StateDependencies> dependencies) :
                                dependencies_(std::move(dependencies)) {

}

std::shared_ptr<WizardStateInterface> DeleteTaskState::Execute(std::shared_ptr<WizardContext> context) {
    std::optional<TaskId> task_id = dependencies_->GetTaskIdFromUser();
    if (!task_id.has_value()){
        dependencies_->GetConsolePrinter()->WriteError("Incorrect task id was given, try again!");
        return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
    }

    switch (dependencies_->GetController()->DeleteTask(task_id.value())) {
        case TaskActionResult::SUCCESS: {
            dependencies_->GetConsolePrinter()->WriteLine("Task was successfully deleted.");
            return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
        }
        case TaskActionResult::FAIL_CONTROVERSIAL_SUBTASKS: {
            if (dependencies_->UserConfirm("Found subtasks for this task, are you sure you want to delete them?")) {
                dependencies_->GetController()->DeleteTaskWithSubTasks(task_id.value());
                dependencies_->GetConsolePrinter()->WriteLine("Deleted task with it's subtasks.");
                return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
            } else {
                dependencies_->GetConsolePrinter()->WriteLine("Task wasn't deleted.");
                return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
            }
        }
        default: {
            dependencies_->GetConsolePrinter()->WriteError("No task was found with such task id");
            return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
        }
    }
}
