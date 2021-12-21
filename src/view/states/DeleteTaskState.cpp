//
// Created by Maksym Kharchenko on 02.12.2021.
//

#include "DeleteTaskState.h"
#include "console_io/ConsoleUtilities.h"

DeleteTaskState::DeleteTaskState(const std::shared_ptr<StatesFactory>& factory) :
                                factory_(factory) {

}

std::shared_ptr<StateInterface> DeleteTaskState::Execute(std::shared_ptr<StateContext> context) {
    std::optional<TaskId> task_id = console_io::util::GetTaskIdFromUser("Task ID", *factory_.lock()->GetConsolePrinter(), *factory_.lock()->GetConsoleReader());
    if (!task_id.has_value()){
        factory_.lock()->GetConsolePrinter()->WriteError("Incorrect task id was given, try again!");
        return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::PREVIOUS);
    }

    switch (factory_.lock()->GetController()->DeleteTask(task_id.value())) {
        case TaskActionResult::SUCCESS: {
            factory_.lock()->GetConsolePrinter()->WriteLine("Task was successfully deleted.");
            return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::PREVIOUS);
        }
        case TaskActionResult::FAIL_CONTROVERSIAL_SUBTASKS: {
            if (console_io::util::UserConfirm("Found subtasks for this task, are you sure you want to delete them?", *factory_.lock()->GetConsolePrinter(), *factory_.lock()->GetConsoleReader())) {
                factory_.lock()->GetController()->DeleteTaskWithSubTasks(task_id.value());
                factory_.lock()->GetConsolePrinter()->WriteLine("Deleted task with it's subtasks.");
                return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::PREVIOUS);
            } else {
                factory_.lock()->GetConsolePrinter()->WriteLine("Task wasn't deleted.");
                return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::PREVIOUS);
            }
        }
        default: {
            factory_.lock()->GetConsolePrinter()->WriteError("No task was found with such task id");
            return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::ERROR);
        }
    }
}
