//
// Created by Maksym Kharchenko on 06.12.2021.
//

#include "SetLabelState.h"
#include "user_interface/console_io/ConsoleUtilities.h"

SetLabelState::SetLabelState(const StateType next_state,
                             const StateType error_state,
                             const std::shared_ptr<ConsolePrinter>& printer,
                             const std::shared_ptr<ConsoleReader>& reader,
                             const std::shared_ptr<CommandFactory>& command_factory) :
                             next_state_(next_state),
                             error_state_(error_state),
                             printer_(printer),
                             reader_(reader),
                             command_factory_(command_factory) {}

StateType SetLabelState::Execute(StateContext& context) {
    std::optional<TaskId> task_id =
            console_io::util::GetTaskIdFromUser("Task ID", *printer_, *reader_);
    if (!task_id.has_value()){
        printer_->WriteError("Incorrect task id was given, try again!");
        return error_state_;
    }

    std::string label_to_set = console_io::util::GetUserInput("Label", *printer_, *reader_);
    context.SetTaskId(task_id.value());
    context.SetTaskLabel(label_to_set);
    context.SetCommand(command_factory_->CreateSetLabelCommand(context));
    return next_state_;
}
