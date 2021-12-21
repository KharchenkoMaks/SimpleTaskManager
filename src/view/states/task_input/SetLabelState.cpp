//
// Created by Maksym Kharchenko on 06.12.2021.
//

#include "SetLabelState.h"
#include "console_io/ConsoleUtilities.h"

SetLabelState::SetLabelState(const std::shared_ptr<StatesFactory>& factory) :
                            factory_(factory) {

}

std::shared_ptr<StateInterface> SetLabelState::Execute(std::shared_ptr<StateContext> context) {
    std::optional<TaskId> task_id = console_io::util::GetTaskIdFromUser("Task ID", *factory_.lock()->GetConsolePrinter(), *factory_.lock()->GetConsoleReader());
    if (!task_id.has_value()){
        factory_.lock()->GetConsolePrinter()->WriteError("Incorrect task id was given, try again!");
        return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::PREVIOUS);
    }

    std::string label_to_set = console_io::util::GetUserInput("Label", *factory_.lock()->GetConsolePrinter(), *factory_.lock()->GetConsoleReader());
    TaskActionResult set_label_result = factory_.lock()->GetController()->SetTaskLabel(task_id.value(), label_to_set);
    switch (set_label_result) {
        case TaskActionResult::SUCCESS: {
            factory_.lock()->GetConsolePrinter()->WriteLine("Label was successfully set.");
            return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::NEXT);
        }
        default: {
            factory_.lock()->GetConsolePrinter()->WriteError("Task with such id wasn't found.");
            return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::ERROR);
        }
    }
}
