//
// Created by Maksym Kharchenko on 01.12.2021.
//

#include "CompleteTaskState.h"
#include "user_interface/console_io/ConsoleUtilities.h"

CompleteTaskState::CompleteTaskState(const std::shared_ptr<StatesFactory>& factory) :
                                    factory_(factory) {

}

std::shared_ptr<StateInterface> CompleteTaskState::Execute(std::shared_ptr<StateContext> context) {
    std::optional<TaskId> task_id = console_io::util::GetTaskIdFromUser("Task ID", *factory_.lock()->GetConsolePrinter(), *factory_.lock()->GetConsoleReader());
    if (!task_id.has_value()) {
        factory_.lock()->GetConsolePrinter()->WriteError("Incorrect task id was given, try again!");
        return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::PREVIOUS);
    }

    switch (factory_.lock()->GetController()->CompleteTask(task_id.value())) {
        case TaskActionResult::SUCCESS: {
            factory_.lock()->GetConsolePrinter()->WriteLine("Task successfully completed.");
            return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::PREVIOUS);
        }
        case TaskActionResult::FAIL_CONTROVERSIAL_SUBTASKS: {
            if (console_io::util::UserConfirm("Found uncompleted subtasks, do you want to complete them?", *factory_.lock()->GetConsolePrinter(), *factory_.lock()->GetConsoleReader())) {
                factory_.lock()->GetController()->CompleteTaskWithSubTasks(task_id.value());
                factory_.lock()->GetConsolePrinter()->WriteLine("Completed task with it subtasks.");
                return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::PREVIOUS);
            } else {
                factory_.lock()->GetConsolePrinter()->WriteLine("Task wasn't completed because of uncompleted subtasks");
                return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::PREVIOUS);
            }
        }
        default: {
            factory_.lock()->GetConsolePrinter()->WriteError("No task with this id");
            return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::ERROR);
        }
    }
}
