//
// Created by Maksym Kharchenko on 06.12.2021.
//

#include "SetLabelState.h"

SetLabelState::SetLabelState(std::unique_ptr<StateDependencies> dependencies) :
                            dependencies_(std::move(dependencies)) {

}

std::shared_ptr<WizardStateInterface> SetLabelState::Execute(std::shared_ptr<WizardContext> context) {
    std::optional<TaskId> task_id = dependencies_->GetTaskIdFromUser();
    if (!task_id.has_value()){
        dependencies_->GetConsolePrinter()->WriteError("Incorrect task id was given, try again!");
        return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
    }

    std::string label_to_set = dependencies_->GetUserInput("Label");
    TaskActionResult set_label_result = dependencies_->GetController()->SetTaskLabel(task_id.value(), label_to_set);
    switch (set_label_result) {
        case TaskActionResult::SUCCESS: {
            dependencies_->GetConsolePrinter()->WriteLine("Label was successfully set.");
            return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT);
        }
        default: {
            dependencies_->GetConsolePrinter()->WriteError("Task with such id wasn't found.");
            return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
        }
    }
}
