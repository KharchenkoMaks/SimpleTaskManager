//
// Created by Maksym Kharchenko on 24.11.2021.
//

#ifndef SIMPLETASKMANAGER_INPUTTASKDUEDATESTATE_H
#define SIMPLETASKMANAGER_INPUTTASKDUEDATESTATE_H

#include "states/abstract/WizardStatePrinter.h"
#include "states/factory/WizardStatesFactory.h"
#include "context/WizardContext.h"

#include <string>
#include <memory>
#include <ctime>

class InputTaskDueDateState : public WizardStatePrinter {
public:
    explicit InputTaskDueDateState(const std::shared_ptr<ConsolePrinter>& printer);
public:
    std::optional<std::shared_ptr<IWizardState>> Execute(std::shared_ptr<WizardContext> context,
                                          std::shared_ptr<WizardStatesFactory> state_factory) override;
};


#endif //SIMPLETASKMANAGER_INPUTTASKDUEDATESTATE_H
