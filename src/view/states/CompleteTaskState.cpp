//
// Created by Maksym Kharchenko on 01.12.2021.
//

#include "CompleteTaskState.h"

CompleteTaskState::CompleteTaskState(std::unique_ptr<StateDependencies> dependencies) :
                                    dependencies_(std::move(dependencies)) {

}

std::shared_ptr<WizardStateInterface> CompleteTaskState::Execute(std::shared_ptr<WizardContext> context) {
    std::optional<TaskId> task_id = dependencies_->GetTaskIdFromUser();
    if (!task_id.has_value()) {
        dependencies_->GetConsolePrinter()->WriteError("Incorrect task id was given, try again!");
        return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
    }

    switch (dependencies_->GetController()->CompleteTask(task_id.value())) {
        case TaskActionResult::SUCCESS: {
            dependencies_->GetConsolePrinter()->WriteLine("Task successfully completed.");
            return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
        }
        case TaskActionResult::FAIL_CONTROVERSIAL_SUBTASKS: {
            if (dependencies_->UserConfirm("Found uncompleted subtasks, do you want to complete them?")) {
                dependencies_->GetController()->CompleteTaskWithSubTasks(task_id.value());
                dependencies_->GetConsolePrinter()->WriteLine("Completed task with it subtasks.");
                return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
            } else {
                dependencies_->GetConsolePrinter()->WriteLine("Task wasn't completed because of uncompleted subtasks");
                return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
            }
        }
        default: {
            dependencies_->GetConsolePrinter()->WriteError("No task with this id");
            return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
        }
    }
}
