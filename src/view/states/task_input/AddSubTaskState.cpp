//
// Created by Maksym Kharchenko on 02.12.2021.
//

#include "AddSubTaskState.h"
#include "ConsoleStateMachine.h"

AddSubTaskState::AddSubTaskState(const std::shared_ptr<Controller> &controller,
                                 const std::shared_ptr<WizardStatesFactory> &states_factory,
                                 const std::shared_ptr<ConsolePrinter> &printer,
                                 const std::shared_ptr<ConsoleReader> &reader) : WizardStateController(controller,
                                                                                                       states_factory,
                                                                                                       printer,
                                                                                                       reader) {

}

std::optional<std::shared_ptr<WizardStateConsole>> AddSubTaskState::Execute(std::shared_ptr<WizardContext> context) {
    std::optional<TaskId> parent_task_id = GetTaskIdFromUser();
    if (!parent_task_id.has_value()){
        GetConsolePrinter()->WriteError("Wrong task id was given, try again!");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
    }

    std::optional<Task> task_to_edit = GetController()->GetTask(parent_task_id.value());
    if (!task_to_edit.has_value()) {
        GetConsolePrinter()->WriteError("No task with such task id was found, try again.");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
    }

    ConsoleStateMachine state_machine(std::make_shared<WizardContext>(),
                                     GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT));
    std::shared_ptr<WizardContext> context_with_added_task = state_machine.Run();

    std::optional<TaskId> added_subtask_id = GetController()->AddSubTask(context_with_added_task->GetTask().value(),
                                                                         parent_task_id.value());
    if (added_subtask_id.has_value()) {
        GetConsolePrinter()->WriteLine("SubTask was successfully added. Task id: " +
                                        std::to_string(added_subtask_id.value().GetId()));

    } else {
        GetConsolePrinter()->WriteError("Given subtask wasn't saved, try again.");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
    }

    return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
}
