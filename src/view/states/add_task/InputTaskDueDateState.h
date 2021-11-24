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

class InputTaskDueDateState : public WizardStatePrinter {
public:
    explicit InputTaskDueDateState(std::shared_ptr<ConsolePrinter> printer);
public:
    std::shared_ptr<IWizardState> Execute(std::shared_ptr<WizardContext> context,
                                          std::shared_ptr<WizardStatesFactory> state_factory) override;
};


#endif //SIMPLETASKMANAGER_INPUTTASKDUEDATESTATE_H
