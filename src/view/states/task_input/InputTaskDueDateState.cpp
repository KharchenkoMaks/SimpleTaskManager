//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/InputTaskDueDateState.h"
#include "utilities/TaskConvertors.h"
#include "user_interface/console_io/ConsoleUtilities.h"

InputTaskDueDateState::InputTaskDueDateState(const std::shared_ptr<StatesFactory>& factory) :
                                             factory_(factory) {

}

std::shared_ptr<StateInterface> InputTaskDueDateState::Execute(StateContext& context) {
    std::string user_input =
            console_io::util::GetUserInput("Due Date, format: 12:00 01.01.2000", *factory_.lock()->GetConsolePrinter(), *factory_.lock()->GetConsoleReader());

    std::optional<google::protobuf::Timestamp> task_due_date = StringToTime(user_input);
    if (!task_due_date.has_value()) {
        task_due_date = StringToTime(user_input, "%d.%m.%Y");
    }
    if (task_due_date.has_value()) {
        const bool due_time_adding_result = context.AddTaskDueTime(task_due_date.value());
        if (!due_time_adding_result) {
            factory_.lock()->GetConsolePrinter()->WriteError("Due time should be in future, try again!");
            return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::ERROR);
        }
    } else {
        factory_.lock()->GetConsolePrinter()->WriteError("Wrong due date was given, try again!");
        return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::ERROR);
    }

    return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::NEXT);
}
