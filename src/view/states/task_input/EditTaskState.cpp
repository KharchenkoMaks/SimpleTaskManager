//
// Created by Maksym Kharchenko on 25.11.2021.
//

#include "states/task_input/EditTaskState.h"
#include "ConsoleStateMachine.h"

EditTaskState::EditTaskState(const std::shared_ptr<Controller>& controller,
                             const std::shared_ptr<WizardStatesFactory>& states_factory,
                             const std::shared_ptr<ConsolePrinter>& printer,
                             const std::shared_ptr<ConsoleReader>& reader) :
                             WizardStateController(controller, states_factory, printer, reader) {

}

std::optional<std::shared_ptr<WizardStateConsole>> EditTaskState::Execute(std::shared_ptr<WizardContext> context) {
    std::optional<TaskId> editing_task_id = GetTaskIdFromUser();
    if (!editing_task_id){
        GetConsolePrinter()->WriteError("Wrong task id was given, try again!");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
    }

    ConsoleStateMachine state_machine(GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT));
    std::shared_ptr<WizardContext> context_with_edited_task = state_machine.Run();

//    context->AddTaskTitle(context_with_edited_task->GetAddedTask().GetTitle());
//    context->AddTaskPriority(context_with_edited_task->GetAddedTask().GetPriority());
//    context->AddTaskDueTime(context_with_edited_task->GetAddedTask().GetDueTime());

    return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
}
