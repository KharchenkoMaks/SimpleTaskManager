//
// Created by Maksym Kharchenko on 25.11.2021.
//

#include "states/task_input/EditTaskState.h"

EditTaskState::EditTaskState(const std::shared_ptr<ConsoleStateMachine>& state_machine,
                             const std::shared_ptr<Controller>& controller,
                             const std::shared_ptr<WizardStatesFactory>& states_factory,
                             const std::shared_ptr<ConsolePrinter>& printer,
                             const std::shared_ptr<ConsoleReader>& reader) :
                             WizardStateWithStateMachine(state_machine,
                                                         controller,
                                                         states_factory,
                                                         printer,
                                                         reader) {

}

std::optional<std::shared_ptr<WizardStateConsole>> EditTaskState::Execute(std::shared_ptr<WizardContext> context) {
    std::optional<TaskId> editing_task_id = GetTaskIdFromUser();
    if (!editing_task_id.has_value()) {
        GetConsolePrinter()->WriteError("Incorrect task id was given, try again!");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
    }

    // Creating new context
    std::shared_ptr<WizardContext> context_task_editing = std::make_shared<WizardContext>();
    // Setting task to edit in context
    context_task_editing->SetEditingTask(editing_task_id.value(),
                                         GetController()->GetTask(editing_task_id.value()).value());

    context_task_editing = RunStateMachine(context_task_editing,
                    GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT));

    // Giving edited task to controller
    if (!GetController()->EditTask(context_task_editing->GetTaskId().value(), context_task_editing->GetTask().value())) {
        GetConsolePrinter()->WriteError("Task wasn't edited, try again.");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
    }

    return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
}
