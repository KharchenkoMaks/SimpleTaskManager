//
// Created by Maksym Kharchenko on 02.12.2021.
//

#include "DeleteTaskState.h"
#include "user_interface/console_io/ConsoleUtilities.h"

DeleteTaskState::DeleteTaskState(const StateType next_state,
                                 const StateType error_state,
                                 const std::shared_ptr<ConsolePrinter>& printer,
                                 const std::shared_ptr<ConsoleReader>& reader,
                                 const std::shared_ptr<CommandFactory>& command_factory) :
                                 next_state_(next_state),
                                 error_state_(error_state),
                                 printer_(printer),
                                 reader_(reader),
                                 command_factory_(command_factory) {}

StateType DeleteTaskState::Execute(StateContext& context) {
    std::optional<TaskId> task_id = console_io::util::GetTaskIdFromUser("Task ID", *printer_, *reader_);
    if (!task_id.has_value()){
        printer_->WriteError("Incorrect task id was given, try again!");
        return error_state_;
    }

    context.SetTaskId(task_id.value());
    context.SetCommand(command_factory_->CreateDeleteCommand(context, console_io::util::UserConfirm("Delete all subtasks?",
                                                                                                    *printer_,
                                                                                                    *reader_)));
    return next_state_;
}
