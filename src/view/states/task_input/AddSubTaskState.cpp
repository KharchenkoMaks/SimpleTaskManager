//
// Created by Maksym Kharchenko on 02.12.2021.
//

#include "AddSubTaskState.h"
#include "console_io/ConsoleUtilities.h"

AddSubTaskState::AddSubTaskState(const std::shared_ptr<StatesFactory>& factory) : factory_(factory) {

}

std::shared_ptr<StateInterface> AddSubTaskState::Execute(std::shared_ptr<StateContext> context) {
    std::optional<TaskId> parent_task_id = console_io::util::GetTaskIdFromUser("Parent Task ID", *factory_.lock()->GetConsolePrinter(), *factory_.lock()->GetConsoleReader());
    if (!parent_task_id.has_value()) {
        factory_.lock()->GetConsolePrinter()->WriteError("Incorrect task id was given, try again!");
        return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::PREVIOUS);
    }

    auto state_machine = factory_.lock()->CreateStateMachine();

    std::shared_ptr<StateContext> context_with_added_task =
            state_machine->Run(std::make_shared<StateContext>(),
                                           factory_.lock()->GetNextState(*this,StatesFactory::MoveType::NEXT));

    std::pair<TaskActionResult, std::optional<TaskId>> added_subtask_result = GiveSubTaskToController(parent_task_id.value(),
                                                                                                      context_with_added_task);

    return PrintResultAndChangeState(added_subtask_result);
}

void AddSubTaskState::ShowAddedTaskId(const TaskId& task_id) {
    factory_.lock()->GetConsolePrinter()->WriteLine("Subtask was successfully added. Task id: " + std::to_string(task_id.id()));
}

std::pair<TaskActionResult, std::optional<TaskId>> AddSubTaskState::GiveSubTaskToController(const TaskId& parent_id, const std::shared_ptr<StateContext>& context_with_added_task) {
    if (context_with_added_task->GetTask().has_value()) {
        return factory_.lock()->GetController()->AddSubTask(context_with_added_task->GetTask().value(), parent_id);
    }
    return std::pair(TaskActionResult::FAIL_INVALID_TASK, std::nullopt);
}

std::shared_ptr<StateInterface> AddSubTaskState::PrintResultAndChangeState(const std::pair<TaskActionResult, std::optional<TaskId>>& added_subtask_result) {
    switch (added_subtask_result.first) {
        case TaskActionResult::SUCCESS: {
            ShowAddedTaskId(added_subtask_result.second.value());
            return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::PREVIOUS);
        }
        case TaskActionResult::FAIL_NO_SUCH_TASK: {
            factory_.lock()->GetConsolePrinter()->WriteError("No parent task with this id was found.");
            return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::ERROR);
        }
        default: {
            factory_.lock()->GetConsolePrinter()->WriteError("Invalid task was given, try again.");
            return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::ERROR);
        }
    }
}
