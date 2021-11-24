//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_WIZARDCONTEXT_H
#define SIMPLETASKMANAGER_WIZARDCONTEXT_H

#include <memory>

class WizardContext {
public:
    WizardContext();
public:
    bool IsWizardEnded();
public:
    void QuitWizard();
private:
    bool wizard_quit_;
};


#endif //SIMPLETASKMANAGER_WIZARDCONTEXT_H
