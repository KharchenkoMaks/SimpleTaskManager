//
// Created by Maksym Kharchenko on 01.12.2021.
//

#include "CompleteTaskState.h"
#include "user_interface/console_io/ConsoleUtilities.h"

CompleteTaskState::CompleteTaskState(const std::shared_ptr<StatesFactory>& factory) :
                                    factory_(factory) {

}

std::shared_ptr<StateInterface> CompleteTaskState::Execute(StateContext& context) {
    std::optional<TaskId> task_id = console_io::util::GetTaskIdFromUser("Task ID", *factory_.lock()->GetConsolePrinter(), *factory_.lock()->GetConsoleReader());
    if (!task_id.has_value()) {
        factory_.lock()->GetConsolePrinter()->WriteError("Incorrect task id was given, try again!");
        return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::ERROR);
    }

    context.SetTaskId(task_id.value());
    context.SetCommand(factory_.lock()->GetCommandFactory()->CreateCompleteCommand(context, console_io::util::UserConfirm("Complete all subtasks?", *factory_.lock()->GetConsolePrinter(), *factory_.lock()->GetConsoleReader())));
    return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::PREVIOUS);
}
