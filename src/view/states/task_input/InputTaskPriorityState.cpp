//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/InputTaskPriorityState.h"
#include "utilities/TaskConvertors.h"
#include "user_interface/console_io/ConsoleUtilities.h"

InputTaskPriorityState::InputTaskPriorityState(const StateType next_state,
                                               const StateType error_state,
                                               const std::shared_ptr<ConsolePrinter>& printer,
                                               const std::shared_ptr<ConsoleReader>& reader) :
                                               next_state_(next_state),
                                               error_state_(error_state),
                                               printer_(printer),
                                               reader_(reader) {}

StateType InputTaskPriorityState::Execute(StateContext& context) {
    std::string user_input =
            console_io::util::GetUserInput("Priority (High, Medium, Low, None)", *printer_, *reader_);

    std::optional<Task::Priority> task_priority = StringToTaskPriority(user_input);
    if (task_priority.has_value()) {
        context.AddTaskPriority(task_priority.value());
    } else if (!user_input.empty()) {
        printer_->WriteError("Wrong task priority was given, try [High, Medium, Low, None]!");
        return error_state_;
    }

    return next_state_;
}
