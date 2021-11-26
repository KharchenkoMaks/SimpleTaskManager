//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_WIZARDSTATEPRINTER_H
#define SIMPLETASKMANAGER_WIZARDSTATEPRINTER_H

#include "states/abstract/IWizardState.h"
#include "console_io/ConsolePrinter.h"
#include "console_io/ConsoleReader.h"

#include <memory>

class WizardStatePrinter : public IWizardState {
public:
    explicit WizardStatePrinter(const std::shared_ptr<ConsolePrinter>& printer,
                                const std::shared_ptr<ConsoleReader>& reader);
    
    virtual ~WizardStatePrinter() = default;

protected:
   std::shared_ptr<ConsolePrinter> console_printer_;
   std::shared_ptr<ConsoleReader> console_reader_;
};


#endif //SIMPLETASKMANAGER_WIZARDSTATEPRINTER_H
