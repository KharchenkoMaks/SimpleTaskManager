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
    // TODO (Maksym): Move task_id checks to method in WizardStateController
    std::optional<TaskId> task_id = GetTaskIdFromUser();
    if (!task_id.has_value()){
        GetConsolePrinter()->WriteError("Wrong task id was given, try again!");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
    }

    std::optional<Task> task_to_edit = GetController()->GetTask(task_id.value());
    if (!task_to_edit.has_value()) {
        GetConsolePrinter()->WriteError("No task with such task id was found, try again.");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
    }

    if (!GetController()->CompleteTask(task_id.value())){
        GetConsolePrinter()->WriteError("Task wasn't completed, try again.");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
    }

    return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
}
