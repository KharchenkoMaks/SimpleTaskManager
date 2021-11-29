//
// Created by Maksym Kharchenko on 25.11.2021.
//

#include "states/task_input/EditTaskState.h"
#include "ConsoleStateMachine.h"

EditTaskState::EditTaskState(const std::shared_ptr<WizardStatesFactory>& states_factory,
                             const std::shared_ptr<ConsolePrinter>& printer,
                             const std::shared_ptr<ConsoleReader>& reader) :
                             WizardStateConsole(states_factory, printer, reader) {

}

std::optional<std::shared_ptr<IWizardState>> EditTaskState::Execute(std::shared_ptr<WizardContext> context) {
    std::optional<TaskId> editing_task_id = GetTaskIdFromUser();
    if (!editing_task_id){
        GetConsolePrinter()->WriteError("Wrong task id was given, try again!");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
    }

    std::shared_ptr<WizardContext> context_with_edited_task = std::make_shared<WizardContext>();
    ConsoleStateMachine state_machine(context_with_edited_task,
                                      GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT));
    state_machine.Run();

    context->AddTaskTitle(context_with_edited_task->GetAddedTask().GetTitle());
    context->AddTaskPriority(context_with_edited_task->GetAddedTask().GetPriority());
    context->AddTaskDueTime(context_with_edited_task->GetAddedTask().GetDueTime());

    return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
}
