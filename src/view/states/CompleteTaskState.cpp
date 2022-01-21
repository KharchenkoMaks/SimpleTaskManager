//
// Created by Maksym Kharchenko on 01.12.2021.
//

#include "CompleteTaskState.h"
#include "user_interface/console_io/ConsoleUtilities.h"

CompleteTaskState::CompleteTaskState(const std::shared_ptr<StatesFactory>& factory) :
                                    factory_(factory) {

}

std::shared_ptr<State> CompleteTaskState::Execute(StateContext& context) {
    std::optional<TaskId> task_id = console_io::util::GetTaskIdFromUser("Task ID", *factory_->GetConsolePrinter(), *factory_->GetConsoleReader());
    if (!task_id.has_value()) {
        factory_->GetConsolePrinter()->WriteError("Incorrect task id was given, try again!");
        return factory_->GetNextState(*this, StatesFactory::MoveType::ERROR);
    }

    context.SetTaskId(task_id.value());
    context.SetCommand(factory_->GetCommandFactory()->CreateCompleteCommand(context, console_io::util::UserConfirm("Complete all subtasks?", *factory_->GetConsolePrinter(), *factory_->GetConsoleReader())));
    return factory_->GetNextState(*this, StatesFactory::MoveType::PREVIOUS);
}
