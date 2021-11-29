//
// Created by Maksym Kharchenko on 24.11.2021.
//

#ifndef SIMPLETASKMANAGER_INPUTTASKPRIORITYSTATE_H
#define SIMPLETASKMANAGER_INPUTTASKPRIORITYSTATE_H

#include "states/abstract/WizardStateConsole.h"
#include "states/factory/WizardStatesFactory.h"
#include "WizardContext.h"

#include <string>
#include <memory>

class InputTaskPriorityState : public WizardStateConsole {
public:
    explicit InputTaskPriorityState(const std::shared_ptr<WizardStatesFactory>& states_factory,
                                    const std::shared_ptr<ConsolePrinter>& printer,
                                    const std::shared_ptr<ConsoleReader>& reader);
public:
    std::optional<std::shared_ptr<IWizardState>> Execute(std::shared_ptr<WizardContext> context) override;
};


#endif //SIMPLETASKMANAGER_INPUTTASKPRIORITYSTATE_H
