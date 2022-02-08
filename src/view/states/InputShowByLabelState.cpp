//
// Created by Maksym Kharchenko on 21.01.2022.
//

#include "InputShowByLabelState.h"
#include "view/user_interface/console_io/ConsoleUtilities.h"

InputShowByLabelState::InputShowByLabelState(const StateType next_state,
                                             const std::shared_ptr<ConsolePrinter>& printer,
                                             const std::shared_ptr<ConsoleReader>& reader) :
                                             next_state_(next_state),
                                             printer_(printer),
                                             reader_(reader) {}

StateType InputShowByLabelState::Execute(StateContext& context) {
    const std::string users_label =
            console_io::util::GetUserInput("Label to sort by", *printer_, *reader_);

    context.SetTaskLabel(users_label);
    return next_state_;
}