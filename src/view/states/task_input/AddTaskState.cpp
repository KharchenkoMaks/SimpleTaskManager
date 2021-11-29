//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/AddTaskState.h"
#include "ConsoleStateMachine.h"

std::optional<std::shared_ptr<IWizardState>> AddTaskState::Execute(std::shared_ptr<WizardContext> context) {

    std::shared_ptr<WizardContext> context_with_added_task = std::make_shared<WizardContext>();
    ConsoleStateMachine state_machine(context_with_added_task,
                                      GetStatesFactory(),
                                      GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT));
    state_machine.Run();

    context->AddTaskTitle(context_with_added_task->GetAddedTask().GetTitle());
    context->AddTaskPriority(context_with_added_task->GetAddedTask().GetPriority());
    context->AddTaskDueTime(context_with_added_task->GetAddedTask().GetDueTime());

    return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
}

AddTaskState::AddTaskState(const std::shared_ptr<WizardStatesFactory> &states_factory) : IWizardState(states_factory) {

}
