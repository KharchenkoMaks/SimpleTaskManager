//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "states/quit/QuitState.h"

std::shared_ptr<IWizardState> QuitState::Execute(std::shared_ptr<WizardContext> context,
                                                 std::shared_ptr<WizardStatesFactory> state_factory) {

    std::shared_ptr<WizardStatesFactory> new_state_factory = std::make_shared<WizardStatesFactory>();
    std::shared_ptr<IWizardState> new_state = new_state_factory->GetConfirmState();
    std::shared_ptr<WizardContext> new_context = std::make_shared<WizardContext>();
    new_context->SetConfirmMessage("Are you sure you want to quit? No changes will be saved!");
    while (!new_context->IsStateMachineStopped()) {
        new_state = new_state->Execute(new_context, new_state_factory);
    }
    if (new_context->GetConfirmationStatus() == WizardContext::ConfirmationStatus::kConfirmed) {
        context->InterruptStateMachine();
        return state_factory->GetRootState();
    } else if (new_context->GetConfirmationStatus() == WizardContext::ConfirmationStatus::kNone) {
        throw std::runtime_error("Confirmation process was failed.");
    }
    return state_factory->GetRootState();
}