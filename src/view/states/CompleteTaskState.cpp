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
    std::optional<TaskId> task_id = GetTaskIdFromUser();
    if (!task_id.has_value()) {
        GetConsolePrinter()->WriteError("Incorrect task id was given, try again!");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
    }

    switch (GetController()->CompleteTask(task_id.value())) {
        case TaskActionResult::SUCCESS: {
            GetConsolePrinter()->WriteLine("Task successfully completed.");
            return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
        }
        case TaskActionResult::FAIL_CONTROVERSIAL_SUBTASKS: {
            if (UserConfirm("Found uncompleted subtasks, do you want to complete them?")) {
                GetController()->CompleteTaskWithSubTasks(task_id.value());
                GetConsolePrinter()->WriteLine("Completed task with it subtasks.");
                return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
            } else {
                GetConsolePrinter()->WriteLine("Task wasn't completed because of uncompleted subtasks");
                return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
            }
        }
        default: {
            GetConsolePrinter()->WriteError("No task with this id");
            return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
        }
    }
}
