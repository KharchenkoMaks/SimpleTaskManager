//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/InputTaskTitleState.h"
#include "user_interface/console_io/ConsoleUtilities.h"

InputTaskTitleState::InputTaskTitleState(const StateType next_state,
                                         const std::shared_ptr<ConsolePrinter>& printer,
                                         const std::shared_ptr<ConsoleReader>& reader) :
                                         next_state_(next_state),
                                         printer_(printer),
                                         reader_(reader) {}

StateType InputTaskTitleState::Execute(StateContext& context) {
    std::string user_input =
            console_io::util::GetUserInput("Title", *printer_, *reader_);

    if (!user_input.empty())
        context.AddTaskTitle(user_input);

    return next_state_;
}
