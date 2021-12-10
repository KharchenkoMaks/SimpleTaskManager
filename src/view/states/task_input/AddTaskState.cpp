//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/AddTaskState.h"

std::shared_ptr<WizardStateInterface> AddTaskState::Execute(std::shared_ptr<WizardContext> context) {
    std::shared_ptr<WizardContext> context_with_added_task = dependencies_->RunStateMachine(std::make_shared<WizardContext>(),
                    dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT));

    if (context_with_added_task->GetTask().has_value()) {
        std::pair<TaskActionResult, std::optional<TaskId>> add_task_result =
                dependencies_->GetController()->AddTask(context_with_added_task->GetTask().value());
        switch (add_task_result.first) {
            case TaskActionResult::SUCCESS: {
                ShowAddedTaskId(add_task_result.second.value());
                return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
            }
            default: {
                dependencies_->GetConsolePrinter()->WriteError("Invalid task was given, try again.");
                return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
            }
        }
    }
    dependencies_->GetConsolePrinter()->WriteError("Task wasn't saved.");
    return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
}

AddTaskState::AddTaskState(std::unique_ptr<StateDependencies> dependencies) :
                           dependencies_(std::move(dependencies)) {

}

void AddTaskState::ShowAddedTaskId(const TaskId& task_id) {
    dependencies_->GetConsolePrinter()->WriteLine("Task was successfully added. Task id: " + std::to_string(task_id.GetId()));
}
