//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "RootState.h"
#include "user_interface/console_io/ConsoleUtilities.h"

RootState::RootState(const StateType error_state,
                     const std::shared_ptr<ConsolePrinter>& printer,
                     const std::shared_ptr<ConsoleReader>& reader) :
                     error_state_(error_state),
                     printer_(printer),
                     reader_(reader) {}

StateType RootState::Execute(StateContext& context) {
    std::string command = console_io::util::GetUserInput("", *printer_, *reader_);
    StateType next_state = GetStateTypeByUserCommand(command);
    if (next_state == error_state_)
        printer_->WriteError("Unknown command! Use help.");

    return next_state;
}

StateType RootState::GetStateTypeByUserCommand(const std::string& command) {
    if (command == "add") {
        return StateType::kAddTask;
    } else if (command == "add_subtask") {
        return (StateType::kAddSubTask);
    } else if (command == "edit") {
        return (StateType::kEditTask);
    } else if (command == "delete") {
        return (StateType::kDelete);
    } else if (command == "complete") {
        return (StateType::kComplete);
    } else if (command == "show") {
        return (StateType::kInputShowParameters);
    } else if (command == "help") {
        return (StateType::kHelp);
    } else if (command == "quit") {
        return (StateType::kQuit);
    } else if (command == "label") {
        return (StateType::kSetLabel);
    } else if (command == "save") {
        return (StateType::kSave);
    } else if (command == "load") {
        return (StateType::kLoad);
    } else {
        return error_state_;
    }
}
