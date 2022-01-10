//
// Created by Maksym Kharchenko on 06.12.2021.
//

#include "SetLabelState.h"
#include "user_interface/console_io/ConsoleUtilities.h"

SetLabelState::SetLabelState(const std::shared_ptr<StatesFactory>& factory) :
                            factory_(factory) {

}

std::shared_ptr<StateInterface> SetLabelState::Execute(StateContext& context) {
    std::optional<TaskId> task_id =
            console_io::util::GetTaskIdFromUser("Task ID", *factory_.lock()->GetConsolePrinter(), *factory_.lock()->GetConsoleReader());
    if (!task_id.has_value()){
        factory_.lock()->GetConsolePrinter()->WriteError("Incorrect task id was given, try again!");
        return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::ERROR);
    }

    std::string label_to_set = console_io::util::GetUserInput("Label", *factory_.lock()->GetConsolePrinter(), *factory_.lock()->GetConsoleReader());
    context.SetTaskLabel(label_to_set);
    context.SetCommand(factory_.lock()->GetCommandFactory()->CreateSetLabelCommand(context));
    return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::PREVIOUS);
}
