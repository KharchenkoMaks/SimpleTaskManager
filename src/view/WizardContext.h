//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_WIZARDCONTEXT_H
#define SIMPLETASKMANAGER_WIZARDCONTEXT_H

#include <memory>
#include <string>
#include <optional>

class WizardContext {
public:
    enum class ConfirmationStatus{
        kConfirmed,
        kNotConfirmed,
        kNone
    };
public:
    WizardContext();
public:
    void ConfirmAction();
    void NotConfirmAction();
    void ResetActionConfirmation();

    void SetConfirmMessage(const std::string& message);
    void ResetConfirmMessage();
    std::optional<std::string> GetConfirmMessage();
public:
    void QuitWizard();
    bool IsWizardEnded();
private:
    bool wizard_quit_;

    ConfirmationStatus confirmation_;
    std::optional<std::string> confirm_message_;
};


#endif //SIMPLETASKMANAGER_WIZARDCONTEXT_H
