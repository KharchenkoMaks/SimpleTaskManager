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

std::shared_ptr<WizardStateConsole> AddSubTaskState::Execute(std::shared_ptr<WizardContext> context) {
    std::optional<TaskId> parent_task_id = GetTaskIdFromUser("Parent Task ID");
    if (!parent_task_id.has_value()) {
        GetConsolePrinter()->WriteError("Incorrect task id was given, try again!");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
    }

    std::shared_ptr<WizardContext> context_with_added_task = RunStateMachine(std::make_shared<WizardContext>(),
                                                                             GetStatesFactory()->GetNextState(*this,
                                                                                                              WizardStatesFactory::MoveType::NEXT));

    std::pair<TaskActionResult, std::optional<TaskId>> added_subtask_result = GiveSubTaskToController(parent_task_id.value(),
                                                                                                      context_with_added_task);

    return PrintResultAndChangeState(added_subtask_result);
}

void AddSubTaskState::ShowAddedTaskId(const TaskId& task_id) {
    GetConsolePrinter()->WriteLine("Subtask was successfully added. Task id: " + std::to_string(task_id.GetId()));
}

std::pair<TaskActionResult, std::optional<TaskId>> AddSubTaskState::GiveSubTaskToController(const TaskId& parent_id, const std::shared_ptr<WizardContext>& context_with_added_task) {
    if (context_with_added_task->GetTask().has_value()) {
        return GetController()->AddSubTask(context_with_added_task->GetTask().value(), parent_id);
    }
    return std::pair(TaskActionResult::FAIL_INVALID_TASK, std::nullopt);
}

std::shared_ptr<WizardStateConsole> AddSubTaskState::PrintResultAndChangeState(const std::pair<TaskActionResult, std::optional<TaskId>>& added_subtask_result) {
    switch (added_subtask_result.first) {
        case TaskActionResult::SUCCESS: {
            ShowAddedTaskId(added_subtask_result.second.value());
            return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
        }
        case TaskActionResult::FAIL_NO_SUCH_TASK: {
            GetConsolePrinter()->WriteError("No parent task with this id was found.");
            return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
        }
        default: {
            GetConsolePrinter()->WriteError("Invalid task was given, try again.");
            return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
        }
    }
}
