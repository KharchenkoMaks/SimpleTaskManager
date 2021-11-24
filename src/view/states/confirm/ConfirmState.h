//
// Created by Maksym Kharchenko on 24.11.2021.
//

#ifndef SIMPLETASKMANAGER_CONFIRMSTATE_H
#define SIMPLETASKMANAGER_CONFIRMSTATE_H

#include "states/abstract/WizardStatePrinter.h"
#include "states/factory/WizardStatesFactory.h"

#include <string>
#include <memory>

class ConfirmState : public WizardStatePrinter {
public:
    explicit ConfirmState(std::shared_ptr<ConsolePrinter> printer);
public:
    std::shared_ptr<IWizardState> Execute(std::shared_ptr<WizardContext> context,
                                          std::shared_ptr<WizardStatesFactory> state_factory) override;
};


#endif //SIMPLETASKMANAGER_CONFIRMSTATE_H
