//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "WizardContext.h"

WizardContext::WizardContext() {
    wizard_quit_ = false;

    confirm_message_ = std::nullopt;
    confirmation_ = ConfirmationStatus::kNone;
}

// QuitState

void WizardContext::QuitWizard() {
    wizard_quit_ = true;
}

bool WizardContext::IsWizardEnded() {
    return wizard_quit_;
}

// ConfirmState

void WizardContext::SetConfirmMessage(const std::string& message) {
    confirm_message_ = message;
}

void WizardContext::ResetConfirmMessage() {
    confirm_message_ = std::nullopt;
}

std::optional<std::string> WizardContext::GetConfirmMessage() {
    return confirm_message_;
}

void WizardContext::ConfirmAction() {
    confirmation_ = ConfirmationStatus::kConfirmed;
}

void WizardContext::NotConfirmAction() {
    confirmation_ = ConfirmationStatus::kNotConfirmed;
}

void WizardContext::ResetActionConfirmation() {
    confirmation_ = ConfirmationStatus::kNone;
}

WizardContext::ConfirmationStatus WizardContext::GetConfirmationStatus() {
    return confirmation_;
}
