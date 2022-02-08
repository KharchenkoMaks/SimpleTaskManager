//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "QuitState.h"
#include "user_interface/console_io/ConsoleUtilities.h"

StateType QuitState::Execute(StateContext& context) {
    if (console_io::util::UserConfirm("Are you sure?", *printer_, *reader_))
        return next_state_;
    else
        return error_state_;
}

QuitState::QuitState(const StateType next_state,
                     const StateType error_state,
                     const std::shared_ptr<ConsolePrinter>& printer,
                     const std::shared_ptr<ConsoleReader>& reader) :
                     next_state_(next_state),
                     error_state_(error_state),
                     printer_(printer),
                     reader_(reader) {}
