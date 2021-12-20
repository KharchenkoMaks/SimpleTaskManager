//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/AddTaskState.h"
#include "console_io/ConsoleUtilities.h"

std::shared_ptr<WizardStateInterface> AddTaskState::Execute(std::shared_ptr<WizardContext> context) {
    auto state_machine = factory_.lock()->CreateStateMachine();
    std::shared_ptr<WizardContext> context_with_added_task = state_machine->Run(std::make_shared<WizardContext>(),
                    factory_.lock()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT));

    if (context_with_added_task->GetTask().has_value()) {
        std::pair<TaskActionResult, std::optional<TaskId>> add_task_result =
                factory_.lock()->GetController()->AddTask(context_with_added_task->GetTask().value());
        switch (add_task_result.first) {
            case TaskActionResult::SUCCESS: {
                ShowAddedTaskId(add_task_result.second.value());
                return factory_.lock()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
            }
            default: {
                factory_.lock()->GetConsolePrinter()->WriteError("Invalid task was given, try again.");
                return factory_.lock()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
            }
        }
    }
    factory_.lock()->GetConsolePrinter()->WriteError("Task wasn't saved.");
    return factory_.lock()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
}

AddTaskState::AddTaskState(const std::shared_ptr<WizardStatesFactory>& factory) :
                           factory_(factory) {

}

void AddTaskState::ShowAddedTaskId(const TaskId& task_id) {
    factory_.lock()->GetConsolePrinter()->WriteLine("Task was successfully added. Task id: " + std::to_string(task_id.id()));
}
