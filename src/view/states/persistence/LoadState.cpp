//
// Created by Maksym Kharchenko on 16.12.2021.
//

#include "LoadState.h"
#include "user_interface/console_io/ConsoleUtilities.h"

LoadState::LoadState(const StateType next_state,
                     const StateType error_state,
                     const std::shared_ptr<ConsolePrinter>& printer,
                     const std::shared_ptr<ConsoleReader>& reader,
                     const std::shared_ptr<CommandFactory>& command_factory) :
                     next_state_(next_state),
                     error_state_(error_state),
                     printer_(printer),
                     reader_(reader),
                     command_factory_(command_factory) {}

StateType LoadState::Execute(StateContext& context) {
    std::string file_name = console_io::util::GetUserInput("File name", *printer_, *reader_);
    if (file_name.empty()) {
        printer_->WriteError("Invalid file name!");
        return error_state_;
    }
    context.SetFileName(file_name);
    context.SetCommand(command_factory_->CreateLoadCommand(context));
    return next_state_;
}
