//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/InputTaskDueDateState.h"
#include "utilities/TaskConvertors.h"
#include "user_interface/console_io/ConsoleUtilities.h"

InputTaskDueDateState::InputTaskDueDateState(const std::shared_ptr<StatesFactory>& factory) :
                                             factory_(factory) {

}

std::shared_ptr<State> InputTaskDueDateState::Execute(StateContext& context) {
    std::string user_input =
            console_io::util::GetUserInput("Due Date, format: 12:00 01.01.2000", *factory_->GetConsolePrinter(), *factory_->GetConsoleReader());

    std::optional<google::protobuf::Timestamp> task_due_date = StringToTime(user_input);
    if (!task_due_date.has_value()) {
        task_due_date = StringToTime(user_input, "%d.%m.%Y");
    }
    if (task_due_date.has_value()) {
        context.AddTaskDueTime(task_due_date.value());
        if (google::protobuf::util::TimeUtil::TimestampToTimeT(task_due_date.value()) < time(0)) {
            factory_->GetConsolePrinter()->WriteError("Due time should be in future, try again!");
            return factory_->GetNextState(*this, StatesFactory::MoveType::ERROR);
        }
    } else if (!user_input.empty()) {
        factory_->GetConsolePrinter()->WriteError("Wrong due date was given, try again!");
        return factory_->GetNextState(*this, StatesFactory::MoveType::ERROR);
    }

    return factory_->GetNextState(*this, StatesFactory::MoveType::NEXT);
}
