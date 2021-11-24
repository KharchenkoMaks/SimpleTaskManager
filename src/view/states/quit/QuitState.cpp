//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "states/quit/QuitState.h"

std::shared_ptr<IWizardState> QuitState::Execute(std::shared_ptr<WizardContext> context,
                                                 std::shared_ptr<WizardStatesFactory> state_factory) {
    context->QuitWizard();
    return state_factory->GetRootState();
}
