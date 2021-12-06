//
// Created by Maksym Kharchenko on 01.12.2021.
//

#include "CompleteTaskState.h"

CompleteTaskState::CompleteTaskState(const std::shared_ptr<Controller> &controller,
                                     const std::shared_ptr<WizardStatesFactory> &states_factory,
                                     const std::shared_ptr<ConsolePrinter> &printer,
                                     const std::shared_ptr<ConsoleReader> &reader) :
                                     WizardStateController(controller,
                                                           states_factory,
                                                           printer,
                                                           reader) {

}

std::optional<std::shared_ptr<WizardStateConsole>> CompleteTaskState::Execute(std::shared_ptr<WizardContext> context) {
    WizardStateController::TaskIdFromUser task_id = GetTaskIdFromUser();
    if (task_id.answer_status_ == WizardStateController::TaskIdFromUser::AnswerStatus::kNotValid){
        GetConsolePrinter()->WriteError("Wrong task id was given, try again!");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
    } else if (task_id.answer_status_ == WizardStateController::TaskIdFromUser::AnswerStatus::kNoSuchTask) {
        GetConsolePrinter()->WriteError("No task with such task id was found, try again.");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
    }

    switch (GetController()->CompleteTask(task_id.task_id_.value())) {
        case TaskActionResult::SUCCESS: {
            return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
        }
        case TaskActionResult::FAIL_NO_SUCH_TASK: {
            GetConsolePrinter()->WriteError("No task with this id");
            return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
        }
        case TaskActionResult::FAIL_CONTROVERSIAL_SUBTASKS: {

        }
    }
}
