//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/AddTaskState.h"

std::optional<std::shared_ptr<WizardStateConsole>> AddTaskState::Execute(std::shared_ptr<WizardContext> context) {
    std::shared_ptr<WizardContext> context_with_added_task = std::make_shared<WizardContext>();
    RunStateMachine(context_with_added_task,
                    GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT));

    // Giving task to controller
    std::optional<TaskId> added_task_id = GetController()->AddTask(context_with_added_task->GetTask().value());
    if (added_task_id.has_value()) {
        ShowAddedTaskId(added_task_id.value());
    } else {
        GetConsolePrinter()->WriteError("Given task wasn't saved, try again.");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
    }

    return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
}

AddTaskState::AddTaskState(const std::shared_ptr<ConsoleStateMachine>& state_machine,
                           const std::shared_ptr<Controller>& controller,
                           const std::shared_ptr<WizardStatesFactory>& states_factory,
                           const std::shared_ptr<ConsolePrinter>& printer,
                           const std::shared_ptr<ConsoleReader>& reader) :
                           WizardStateWithStateMachine(state_machine, controller, states_factory, printer, reader) {

}

void AddTaskState::ShowAddedTaskId(const TaskId& task_id) {
    GetConsolePrinter()->WriteLine("Task was successfully added. Task id: " + std::to_string(task_id.GetId()));
}
