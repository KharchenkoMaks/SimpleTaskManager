//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/AddTaskState.h"

std::shared_ptr<IWizardState>
AddTaskState::Execute(std::shared_ptr<WizardContext> context,
                      std::shared_ptr<WizardStatesFactory> state_factory) {
    // TODO (Maksym): make ConsoleStateMachine instead of this while loop

    std::shared_ptr<WizardStatesFactory> new_factory = std::make_shared<WizardStatesFactory>();
    std::shared_ptr<WizardContext> new_context = std::make_shared<WizardContext>();
    std::shared_ptr<IWizardState> new_state =
            new_factory->GetState(WizardStatesFactory::States::kInputTaskTitle);

    while (!new_context->IsStateMachineStopped()){
        new_state = new_state->Execute(new_context, new_factory);
    }

    if (new_context->GetAddedTask().has_value()) {
        context->AddTask(new_context->GetAddedTask());
        new_context->ResetAddedTask();
        // TODO (Maksym): make task adding to TaskManager
    } else {
        throw std::runtime_error("Task adding failed.");
    }

    return state_factory->GetState(WizardStatesFactory::States::kRoot);
}
