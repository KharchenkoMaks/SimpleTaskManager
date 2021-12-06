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

    switch (GetController()->DeleteTask(task_id.task_id_.value())) {
        case TaskActionResult::SUCCESS: {
            GetConsolePrinter()->WriteLine("Task was successfully deleted.");
            return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
        }
        case TaskActionResult::FAIL_NO_SUCH_TASK: {
            GetConsolePrinter()->WriteError("No task was found with such task id");
            return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
        }
        case TaskActionResult::FAIL_CONTROVERSIAL_SUBTASKS: {
            if (UserConfirm("Found subtasks for this task, are you sure you want to delete them?")) {
                GetController()->DeleteTaskWithSubTasks(task_id.task_id_.value());
                GetConsolePrinter()->WriteLine("Deleted task with it's subtasks.");
                return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
            } else {
                GetConsolePrinter()->WriteLine("Task wasn't deleted.");
                return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
            }
        }
    }
}
