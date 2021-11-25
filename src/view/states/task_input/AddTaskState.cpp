//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/AddTaskState.h"
#include "ConsoleStateMachine.h"

std::optional<std::shared_ptr<IWizardState>> AddTaskState::Execute(std::shared_ptr<WizardContext> context,
                      std::shared_ptr<WizardStatesFactory> state_factory) {

    ConsoleStateMachine state_machine;
    WizardContext new_context = state_machine.Run(WizardStatesFactory::States::kInputTaskTitle);

    context->AddTaskTitle(new_context.GetAddedTask().GetTitle());
    context->AddTaskPriority(new_context.GetAddedTask().GetPriority());
    context->AddTaskDueTime(new_context.GetAddedTask().GetDueTime());

    return state_factory->GetState(WizardStatesFactory::States::kRoot);
}
