//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/AddTaskState.h"

std::optional<std::shared_ptr<WizardStateConsole>> AddTaskState::Execute(std::shared_ptr<WizardContext> context) {
    std::shared_ptr<WizardContext> context_with_added_task = RunStateMachine(std::make_shared<WizardContext>(),
                    GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT));

    if (context_with_added_task->GetTask().has_value()) {
        std::pair<TaskActionResult, std::optional<TaskId>> add_task_result =
                GetController()->AddTask(context_with_added_task->GetTask().value());
        switch (add_task_result.first) {
            case TaskActionResult::SUCCESS: {
                ShowAddedTaskId(add_task_result.second.value());
                return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
            }
            default: {
                GetConsolePrinter()->WriteError("Invalid task was given, try again.");
                return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
            }
        }
    }
    GetConsolePrinter()->WriteError("Task wasn't saved.");
    return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
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
