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
    WizardStateController::TaskIdFromUser task_id = GetTaskIdFromUser();
    if (task_id.answer_status_ == WizardStateController::TaskIdFromUser::AnswerStatus::kNotValid){
        GetConsolePrinter()->WriteError("Wrong task id was given, try again!");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
    } else if (task_id.answer_status_ == WizardStateController::TaskIdFromUser::AnswerStatus::kNoSuchTask) {
        GetConsolePrinter()->WriteError("No task with such task id was found, try again.");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
    }

    std::string label_to_set = GetUserInput("Label");
    if (GetController()->SetTaskLabel(task_id.task_id_.value(), label_to_set)) {
        GetConsolePrinter()->WriteLine("Label was successfully set.");
    } else {
        GetConsolePrinter()->WriteError("Label wasn't set.");
    }

    return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT);
}
