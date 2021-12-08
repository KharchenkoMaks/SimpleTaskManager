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

std::optional<std::shared_ptr<WizardStateConsole>> SetLabelState::Execute(std::shared_ptr<WizardContext> context) {
    std::optional<TaskId> task_id = GetTaskIdFromUser();
    if (!task_id.has_value()){
        GetConsolePrinter()->WriteError("Incorrect task id was given, try again!");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
    }

    std::string label_to_set = GetUserInput("Label");
    if (GetController()->SetTaskLabel(task_id.value(), label_to_set)) {
        GetConsolePrinter()->WriteLine("Label was successfully set.");
    } else {
        GetConsolePrinter()->WriteError("Label wasn't set.");
    }

    return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT);
}
