//
// Created by Maksym Kharchenko on 02.12.2021.
//

#include "DeleteTaskState.h"

DeleteTaskState::DeleteTaskState(const std::shared_ptr<Controller> &controller,
                                 const std::shared_ptr<WizardStatesFactory> &states_factory,
                                 const std::shared_ptr<ConsolePrinter> &printer,
                                 const std::shared_ptr<ConsoleReader> &reader) : WizardStateController(controller,
                                                                                                       states_factory,
                                                                                                       printer,
                                                                                                       reader) {

}

std::optional<std::shared_ptr<WizardStateConsole>> DeleteTaskState::Execute(std::shared_ptr<WizardContext> context) {
    WizardStateController::TaskIdFromUser task_id = GetTaskIdFromUser();
    if (task_id.answer_status_ == WizardStateController::TaskIdFromUser::AnswerStatus::kNotValid){
        GetConsolePrinter()->WriteError("Wrong task id was given, try again!");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
    } else if (task_id.answer_status_ == WizardStateController::TaskIdFromUser::AnswerStatus::kNoSuchTask) {
        GetConsolePrinter()->WriteError("No task with such task id was found, try again.");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
    }

    if (!GetController()->DeleteTask(task_id.task_id_.value())) {
        GetConsolePrinter()->WriteError("Task wasn't deleted, try again.");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
    }

    return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
}
