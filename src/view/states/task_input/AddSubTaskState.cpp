//
// Created by Maksym Kharchenko on 02.12.2021.
//

#include "AddSubTaskState.h"
#include "user_interface/console_io/ConsoleUtilities.h"

AddSubTaskState::AddSubTaskState(const StateType next_state,
                                 const StateType error_state,
                                 const std::shared_ptr<ConsolePrinter>& printer,
                                 const std::shared_ptr<ConsoleReader>& reader,
                                 const std::shared_ptr<CommandFactory>& command_factory,
                                 std::unique_ptr<ConsoleStateMachine> state_machine) :
                                 next_state_(next_state),
                                 error_state_(error_state),
                                 printer_(printer),
                                 reader_(reader),
                                 command_factory_(command_factory),
                                 state_machine_(std::move(state_machine)) {}

StateType AddSubTaskState::Execute(StateContext& context) {
    std::optional<TaskId> parent_task_id = console_io::util::GetTaskIdFromUser("Parent Task ID", *printer_, *reader_);
    if (!parent_task_id.has_value()) {
        printer_->WriteError("Incorrect task id was given, try again!");
        return error_state_;
    }

    std::shared_ptr<StateContext> context_with_added_task = state_machine_->Run();

    context.SetTaskBuilder(context_with_added_task->GetTaskBuilder());
    context.SetTaskId(parent_task_id.value());
    context.SetCommand(command_factory_->CreateAddSubTaskCommand(context));
    return next_state_;
}
