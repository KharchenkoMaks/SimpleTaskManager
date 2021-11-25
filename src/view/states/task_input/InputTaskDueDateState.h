//
// Created by Maksym Kharchenko on 24.11.2021.
//

#ifndef SIMPLETASKMANAGER_INPUTTASKDUEDATESTATE_H
#define SIMPLETASKMANAGER_INPUTTASKDUEDATESTATE_H

#include "states/abstract/WizardStatePrinter.h"
#include "states/factory/WizardStatesFactory.h"
#include "WizardContext.h"

#include <string>
#include <memory>
#include <ctime>
#include <optional>

class InputTaskDueDateState : public WizardStatePrinter {
public:
    explicit InputTaskDueDateState(const std::shared_ptr<ConsoleMultiFunctionalPrinter>& printer);
public:
    std::optional<std::shared_ptr<IWizardState>> Execute(std::shared_ptr<WizardContext> context,
                                          std::shared_ptr<WizardStatesFactory> state_factory) override;
};


#endif //SIMPLETASKMANAGER_INPUTTASKDUEDATESTATE_H
