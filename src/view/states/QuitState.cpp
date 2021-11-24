//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "QuitState.h"

std::shared_ptr<IWizardState> QuitState::Execute(std::shared_ptr<WizardContext> context) {
    context->QuitWizard();
    return context->GetFactory()->CreateRootState();
}
