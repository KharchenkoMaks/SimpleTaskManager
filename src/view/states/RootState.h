//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_ROOTSTATE_H
#define SIMPLETASKMANAGER_ROOTSTATE_H

#include "abstract/WizardStatePrinter.h"
#include "factory/WizardStatesFactory.h"
#include "context/WizardContext.h"

#include <string>
#include <memory>

class RootState : public WizardStatePrinter {
public:
    explicit RootState(std::shared_ptr<ConsolePrinter> printer);
public:
    std::optional<std::shared_ptr<IWizardState> > Execute(std::shared_ptr<WizardContext> context,
                                          std::shared_ptr<WizardStatesFactory> state_factory) override;
};


#endif //SIMPLETASKMANAGER_ROOTSTATE_H
