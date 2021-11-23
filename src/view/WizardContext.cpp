//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "WizardContext.h"

#include <utility>

std::shared_ptr<WizardStatesFactory> WizardContext::GetFactory() {
    return states_factory_;
}

WizardContext::WizardContext(std::shared_ptr<WizardStatesFactory> factory) : states_factory_(std::move(factory)) {
    wizard_quit_ = false;
}

void WizardContext::QuitWizard() {
    wizard_quit_ = true;
}

bool WizardContext::IsWizardEnded() {
    return wizard_quit_;
}
