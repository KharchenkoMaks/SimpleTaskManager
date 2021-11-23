//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_WIZARDSTATEPRINTER_H
#define SIMPLETASKMANAGER_WIZARDSTATEPRINTER_H

#include "states/abstract/IWizardState.h"
#include "printer/ConsolePrinter.h"

class WizardStatePrinter : public IWizardState {
public:
    explicit WizardStatePrinter(const ConsolePrinter& printer);
    
    virtual ~WizardStatePrinter() = default;

protected:
    ConsolePrinter printer_;
};


#endif //SIMPLETASKMANAGER_WIZARDSTATEPRINTER_H
