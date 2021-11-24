//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "states/quit/QuitState.h"

std::shared_ptr<IWizardState> QuitState::Execute(std::shared_ptr<WizardContext> context,
                                                 std::shared_ptr<WizardStatesFactory> state_factory) {

    // TODO (Maksym): make ConsoleStateMachine instead of this while

    std::shared_ptr<WizardStatesFactory> new_state_factory = std::make_shared<WizardStatesFactory>();
    std::shared_ptr<IWizardState> new_state =
            new_state_factory->GetState(WizardStatesFactory::States::kConfirm);
    std::shared_ptr<WizardContext> new_context = std::make_shared<WizardContext>();
    new_context->SetConfirmMessage("Are you sure you want to quit? No changes will be saved!");
    while (!new_context->IsStateMachineStopped()) {
        new_state = new_state->Execute(new_context, new_state_factory);
    }

    switch (new_context->GetConfirmationStatus()) {
        case WizardContext::ConfirmationStatus::kConfirmed: {
            context->InterruptStateMachine();
            return state_factory->GetState(WizardStatesFactory::States::kQuit);
        }
        case WizardContext::ConfirmationStatus::kNotConfirmed: {
            return state_factory->GetState(WizardStatesFactory::States::kRoot);
        }
        case WizardContext::ConfirmationStatus::kNone: {
            throw std::runtime_error("Confirmation process was failed.");
        }
    }
}