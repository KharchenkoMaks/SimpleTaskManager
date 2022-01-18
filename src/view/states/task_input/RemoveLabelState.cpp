//
// Created by Maksym Kharchenko on 17.01.2022.
//

#include "RemoveLabelState.h"
#include "user_interface/console_io/ConsoleUtilities.h"

RemoveLabelState::RemoveLabelState(const std::shared_ptr<StatesFactory>& factory) : factory_(factory) {

}

std::shared_ptr<State> RemoveLabelState::Execute(StateContext &context) {
    std::optional<TaskId> task_id =
            console_io::util::GetTaskIdFromUser("Task ID", *factory_.lock()->GetConsolePrinter(), *factory_.lock()->GetConsoleReader());
    if (!task_id.has_value()){
        factory_.lock()->GetConsolePrinter()->WriteError("Incorrect task id was given, try again!");
        return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::ERROR);
    }

    std::string label_to_set = console_io::util::GetUserInput("Label", *factory_.lock()->GetConsolePrinter(), *factory_.lock()->GetConsoleReader());
    context.SetTaskId(task_id.value());
    context.SetTaskLabel(label_to_set);
    context.SetCommand(factory_.lock()->GetCommandFactory()->CreateRemoveLabelCommand(context));
    return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::PREVIOUS);
}
