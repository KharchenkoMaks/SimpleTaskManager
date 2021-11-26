//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/AddTaskState.h"
#include "ConsoleStateMachine.h"

std::optional<std::shared_ptr<IWizardState>> AddTaskState::Execute(std::shared_ptr<WizardContext> context,
                      std::shared_ptr<WizardStatesFactory> state_factory) {

    std::shared_ptr<WizardContext> context_with_added_task = std::make_shared<WizardContext>();
    ConsoleStateMachine state_machine(context_with_added_task,
                                      state_factory,
                                      state_factory->GetNextState(*this));
    state_machine.Run();

    context->AddTaskTitle(context_with_added_task->GetAddedTask().GetTitle());
    context->AddTaskPriority(context_with_added_task->GetAddedTask().GetPriority());
    context->AddTaskDueTime(context_with_added_task->GetAddedTask().GetDueTime());

    return state_factory->GetState(WizardStatesFactory::States::kRoot);
}
