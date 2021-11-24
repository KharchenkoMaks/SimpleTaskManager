//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "WizardContext.h"

WizardContext::WizardContext() {
    wizard_quit_ = false;
    confirm_message_ = std::nullopt;
}

void WizardContext::QuitWizard() {
    wizard_quit_ = true;
}

bool WizardContext::IsWizardEnded() {
    return wizard_quit_;
}

void WizardContext::SetConfirmMessage(const std::string& message) {
    confirm_message_ = message;
}

void WizardContext::ResetConfirmMessage() {
    confirm_message_ = std::nullopt;
}

std::optional<std::string> WizardContext::GetConfirmMessage() {
    return confirm_message_;
}
