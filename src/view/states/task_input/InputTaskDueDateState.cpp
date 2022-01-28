//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/InputTaskDueDateState.h"
#include "utilities/TaskConvertors.h"
#include "user_interface/console_io/ConsoleUtilities.h"

InputTaskDueDateState::InputTaskDueDateState(const StateType next_state,
                                             const StateType error_state,
                                             const std::shared_ptr<ConsolePrinter>& printer,
                                             const std::shared_ptr<ConsoleReader>& reader) :
                                             next_state_(next_state),
                                             error_state_(error_state),
                                             printer_(printer),
                                             reader_(reader) {}

StateType InputTaskDueDateState::Execute(StateContext& context) {
    std::string user_input =
            console_io::util::GetUserInput("Due Date, format: 12:00 01.01.2000", *printer_, *reader_);

    std::optional<google::protobuf::Timestamp> task_due_date = StringToTime(user_input);
    if (!task_due_date.has_value()) {
        task_due_date = StringToTime(user_input, "%d.%m.%Y");
    }
    if (task_due_date.has_value()) {
        context.AddTaskDueTime(task_due_date.value());
        if (google::protobuf::util::TimeUtil::TimestampToTimeT(task_due_date.value()) < time(0)) {
            printer_->WriteError("Due time should be in future, try again!");
            return error_state_;
        }
    } else if (!user_input.empty()) {
        printer_->WriteError("Wrong due date was given, try again!");
        return error_state_;
    }

    return next_state_;
}
