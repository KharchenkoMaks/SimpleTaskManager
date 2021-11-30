//
// Created by Maksym Kharchenko on 24.11.2021.
//

#ifndef SIMPLETASKMANAGER_INPUTTASKDUEDATESTATE_H
#define SIMPLETASKMANAGER_INPUTTASKDUEDATESTATE_H

#include "states/abstract/WizardStateConsole.h"
#include "states/factory/WizardStatesFactory.h"
#include "WizardContext.h"

#include <string>
#include <memory>
#include <ctime>
#include <optional>

class InputTaskDueDateState : public WizardStateConsole {
public:
    explicit InputTaskDueDateState(const std::shared_ptr<WizardStatesFactory>& states_factory,
                                   const std::shared_ptr<ConsolePrinter>& printer,
                                   const std::shared_ptr<ConsoleReader>& reader);
public:
    std::optional<std::shared_ptr<WizardStateConsole>> Execute(std::shared_ptr<WizardContext> context) override;
};


#endif //SIMPLETASKMANAGER_INPUTTASKDUEDATESTATE_H
