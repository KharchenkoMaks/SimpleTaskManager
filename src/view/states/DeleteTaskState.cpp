//
// Created by Maksym Kharchenko on 02.12.2021.
//

#include "DeleteTaskState.h"
#include "user_interface/console_io/ConsoleUtilities.h"

DeleteTaskState::DeleteTaskState(const std::shared_ptr<StatesFactory>& factory) :
                                factory_(factory) {

}

std::shared_ptr<StateInterface> DeleteTaskState::Execute(StateContext& context) {
    std::optional<TaskId> task_id = console_io::util::GetTaskIdFromUser("Task ID", *factory_.lock()->GetConsolePrinter(), *factory_.lock()->GetConsoleReader());
    if (!task_id.has_value()){
        factory_.lock()->GetConsolePrinter()->WriteError("Incorrect task id was given, try again!");
        return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::PREVIOUS);
    }

    context.SetTaskId(task_id.value());
    context.SetCommand(factory_.lock()->GetCommandFactory()->CreateDeleteCommand(context));
    return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::PREVIOUS);
}
