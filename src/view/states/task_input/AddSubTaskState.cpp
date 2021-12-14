//
// Created by Maksym Kharchenko on 02.12.2021.
//

#include "AddSubTaskState.h"

AddSubTaskState::AddSubTaskState(std::unique_ptr<StateDependencies> dependencies) : dependencies_(std::move(dependencies)) {

}

std::shared_ptr<WizardStateInterface> AddSubTaskState::Execute(std::shared_ptr<WizardContext> context) {
    std::optional<TaskId> parent_task_id = dependencies_->GetTaskIdFromUser("Parent Task ID");
    if (!parent_task_id.has_value()) {
        dependencies_->GetConsolePrinter()->WriteError("Incorrect task id was given, try again!");
        return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
    }

    std::shared_ptr<WizardContext> context_with_added_task =
            dependencies_->RunStateMachine(std::make_shared<WizardContext>(),
                                           dependencies_->GetStatesFactory()->GetNextState(*this,
                                                                                           WizardStatesFactory::MoveType::NEXT));

    std::pair<TaskActionResult, std::optional<TaskId>> added_subtask_result = GiveSubTaskToController(parent_task_id.value(),
                                                                                                      context_with_added_task);

    return PrintResultAndChangeState(added_subtask_result);
}

void AddSubTaskState::ShowAddedTaskId(const TaskId& task_id) {
    dependencies_->GetConsolePrinter()->WriteLine("Subtask was successfully added. Task id: " + std::to_string(task_id.id()));
}

std::pair<TaskActionResult, std::optional<TaskId>> AddSubTaskState::GiveSubTaskToController(const TaskId& parent_id, const std::shared_ptr<WizardContext>& context_with_added_task) {
    if (context_with_added_task->GetTask().has_value()) {
        return dependencies_->GetController()->AddSubTask(context_with_added_task->GetTask().value(), parent_id);
    }
    return std::pair(TaskActionResult::FAIL_INVALID_TASK, std::nullopt);
}

std::shared_ptr<WizardStateInterface> AddSubTaskState::PrintResultAndChangeState(const std::pair<TaskActionResult, std::optional<TaskId>>& added_subtask_result) {
    switch (added_subtask_result.first) {
        case TaskActionResult::SUCCESS: {
            ShowAddedTaskId(added_subtask_result.second.value());
            return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
        }
        case TaskActionResult::FAIL_NO_SUCH_TASK: {
            dependencies_->GetConsolePrinter()->WriteError("No parent task with this id was found.");
            return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
        }
        default: {
            dependencies_->GetConsolePrinter()->WriteError("Invalid task was given, try again.");
            return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
        }
    }
}
