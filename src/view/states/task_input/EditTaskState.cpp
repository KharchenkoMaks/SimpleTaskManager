//
// Created by Maksym Kharchenko on 25.11.2021.
//

#include "states/task_input/EditTaskState.h"
#include "user_interface/console_io/ConsoleUtilities.h"

EditTaskState::EditTaskState(const std::shared_ptr<StatesFactory>& factory) :
                            factory_(factory) {

}

std::shared_ptr<StateInterface> EditTaskState::Execute(StateContext& context) {
    std::optional<TaskId> editing_task_id = console_io::util::GetTaskIdFromUser("Task ID", *factory_.lock()->GetConsolePrinter(), *factory_.lock()->GetConsoleReader());
    if (!editing_task_id.has_value()) {
        factory_.lock()->GetConsolePrinter()->WriteError("Incorrect task id was given, try again!");
        return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::ERROR);
    }

    auto state_machine = factory_.lock()->CreateStateMachine();
    std::shared_ptr<StateContext> context_with_edited_task =
            state_machine->Run(std::make_shared<StateContext>(),
                    factory_.lock()->GetNextState(*this, StatesFactory::MoveType::NEXT));

    context.SetTaskBuilder(context_with_edited_task->GetTaskBuilder());
    context.SetTaskId(editing_task_id.value());
    context.SetCommand(factory_.lock()->GetCommandFactory()->CreateEditCommand(context));
    return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::PREVIOUS);
}
