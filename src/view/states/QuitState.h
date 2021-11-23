//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_QUITSTATE_H
#define SIMPLETASKMANAGER_QUITSTATE_H

#include "abstract/WizardStatePrinter.h"
#include "WizardContext.h"
#include "factory/WizardStatesFactory.h"

#include <memory>

class QuitState : public WizardStatePrinter {
public:
    explicit QuitState(std::shared_ptr<ConsolePrinter> printer);
public:
    std::shared_ptr<IWizardState> Execute(std::shared_ptr<WizardContext> context) override;
};


#endif //SIMPLETASKMANAGER_QUITSTATE_H
