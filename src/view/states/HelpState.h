//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_HELPSTATE_H
#define SIMPLETASKMANAGER_HELPSTATE_H

#include "printer/ConsolePrinter.h"
#include "factory/WizardStatesFactory.h"
#include "abstract/IWizardState.h"
#include "abstract/WizardStatePrinter.h"

#include <string>

class HelpState : public WizardStatePrinter {
public:
    explicit HelpState(const ConsolePrinter& printer);
public:
    std::shared_ptr<IWizardState> Execute(std::shared_ptr<WizardContext> context) override;
};


#endif //SIMPLETASKMANAGER_HELPSTATE_H
