//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "WizardContext.h"

WizardContext::WizardContext() {
    wizard_quit_ = false;
}

void WizardContext::QuitWizard() {
    wizard_quit_ = true;
}

bool WizardContext::IsWizardEnded() {
    return wizard_quit_;
}
