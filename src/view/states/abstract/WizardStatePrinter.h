//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_WIZARDSTATEPRINTER_H
#define SIMPLETASKMANAGER_WIZARDSTATEPRINTER_H

#include "states/abstract/IWizardState.h"
#include "printer/ConsolePrinter.h"

#include <memory>

class WizardStatePrinter : public IWizardState {
public:
    explicit WizardStatePrinter(std::shared_ptr<ConsolePrinter> printer);
    
    virtual ~WizardStatePrinter() = default;

protected:
   std::shared_ptr<ConsolePrinter> printer_;
};


#endif //SIMPLETASKMANAGER_WIZARDSTATEPRINTER_H