//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_WIZARDSTATEPRINTER_H
#define SIMPLETASKMANAGER_WIZARDSTATEPRINTER_H

#include "states/abstract/IWizardState.h"
#include "ConsoleMultiFunctionalPrinter.h"

#include <memory>

class WizardStatePrinter : public IWizardState {
public:
    explicit WizardStatePrinter(const std::shared_ptr<ConsoleMultiFunctionalPrinter>& printer);
    
    virtual ~WizardStatePrinter() = default;

protected:
   std::shared_ptr<ConsoleMultiFunctionalPrinter> printer_;
};


#endif //SIMPLETASKMANAGER_WIZARDSTATEPRINTER_H
