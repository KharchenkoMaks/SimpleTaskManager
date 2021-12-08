//
// Created by Maksym Kharchenko on 02.12.2021.
//

#include "AddSubTaskState.h"

AddSubTaskState::AddSubTaskState(const std::shared_ptr<ConsoleStateMachine>& state_machine,
                                const std::shared_ptr<Controller>& controller,
                                const std::shared_ptr<WizardStatesFactory>& states_factory,
                                const std::shared_ptr<ConsolePrinter>& printer,
                                const std::shared_ptr<ConsoleReader>& reader) : WizardStateWithStateMachine(state_machine,
                                                                                                            controller,
                                                                                                            states_factory,
                                                                                                            printer,
                                                                                                            reader) {

}

std::optional<std::shared_ptr<WizardStateConsole>> AddSubTaskState::Execute(std::shared_ptr<WizardContext> context) {
    std::optional<TaskId> parent_task_id = GetTaskIdFromUser("Parent Task ID");
    if (!parent_task_id.has_value()){
        GetConsolePrinter()->WriteError("Incorrect task id was given, try again!");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
    }

    std::shared_ptr<WizardContext> context_with_added_task = RunStateMachine(std::make_shared<WizardContext>(),
                    GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT));

    if (context_with_added_task->GetTask().has_value()) {
        std::optional<TaskId> added_subtask_id = GetController()->AddSubTask(context_with_added_task->GetTask().value(),
                                                                             parent_task_id.value());
        if (added_subtask_id.has_value()) {
            ShowAddedTaskId(added_subtask_id.value());
            return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
        }
    }

    GetConsolePrinter()->WriteError("Given subtask wasn't saved, try again.");
    return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
}

void AddSubTaskState::ShowAddedTaskId(const TaskId& task_id) {
    GetConsolePrinter()->WriteLine("Subtask was successfully added. Task id: " + std::to_string(task_id.GetId()));
}
