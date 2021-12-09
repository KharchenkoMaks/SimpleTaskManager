//
// Created by Maksym Kharchenko on 06.12.2021.
//

#include "SetLabelState.h"

SetLabelState::SetLabelState(const std::shared_ptr<Controller> &controller,
                             const std::shared_ptr<WizardStatesFactory> &states_factory,
                             const std::shared_ptr<ConsolePrinter> &printer,
                             const std::shared_ptr<ConsoleReader> &reader) :
                             WizardStateController(controller,
                                                   states_factory,
                                                   printer,
                                                   reader) {

}

std::shared_ptr<WizardStateConsole> SetLabelState::Execute(std::shared_ptr<WizardContext> context) {
    std::optional<TaskId> task_id = GetTaskIdFromUser();
    if (!task_id.has_value()){
        GetConsolePrinter()->WriteError("Incorrect task id was given, try again!");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
    }

    std::string label_to_set = GetUserInput("Label");
    TaskActionResult set_label_result = GetController()->SetTaskLabel(task_id.value(), label_to_set);
    switch (set_label_result) {
        case TaskActionResult::SUCCESS: {
            GetConsolePrinter()->WriteLine("Label was successfully set.");
            return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT);
        }
        default: {
            GetConsolePrinter()->WriteError("Task with such id wasn't found.");
            return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
        }
    }
}
