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
    std::optional<TaskId> task_id = GetTaskIdFromUser();
    if (!task_id.has_value()){
        GetConsolePrinter()->WriteError("Incorrect task id was given, try again!");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
    }

    switch (GetController()->DeleteTask(task_id.value())) {
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
                GetController()->DeleteTaskWithSubTasks(task_id.value());
                GetConsolePrinter()->WriteLine("Deleted task with it's subtasks.");
                return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
            } else {
                GetConsolePrinter()->WriteLine("Task wasn't deleted.");
                return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
            }
        }
    }
}
