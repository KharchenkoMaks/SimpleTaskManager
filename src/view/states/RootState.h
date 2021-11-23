//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_ROOTSTATE_H
#define SIMPLETASKMANAGER_ROOTSTATE_H

#include "abstract/WizardStatePrinter.h"
#include "WizardContext.h"
#include "factory/WizardStatesFactory.h"

class RootState : public WizardStatePrinter {
public:
    explicit RootState(std::shared_ptr<ConsolePrinter> printer);
public:
    std::shared_ptr<IWizardState> Execute(std::shared_ptr<WizardContext> context) override;
};


#endif //SIMPLETASKMANAGER_ROOTSTATE_H
