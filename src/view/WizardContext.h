//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_WIZARDCONTEXT_H
#define SIMPLETASKMANAGER_WIZARDCONTEXT_H

// #include "states/factory/WizardStatesFactory.h"

#include <memory>

class WizardStatesFactory;

class WizardContext {
public:
    explicit WizardContext(std::shared_ptr<WizardStatesFactory> factory);
public:
    std::shared_ptr<WizardStatesFactory> GetFactory();
    bool IsWizardEnded();
public:
    void QuitWizard();
private:
    std::shared_ptr<WizardStatesFactory> states_factory_;
private:
    bool wizard_quit_;
};


#endif //SIMPLETASKMANAGER_WIZARDCONTEXT_H
