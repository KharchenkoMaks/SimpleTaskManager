//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_CONSOLESTATEMACHINE_H
#define SIMPLETASKMANAGER_CONSOLESTATEMACHINE_H

#include "states/factory/WizardStatesFactory.h"
#include "WizardContext.h"
#include "states/abstract/WizardStateConsole.h"

#include <memory>
#include <optional>

class ConsoleStateMachine {
public:
    virtual std::shared_ptr<WizardContext> Run(const std::shared_ptr<WizardContext>& context,
                                       const std::optional<std::shared_ptr<WizardStateConsole>>& initial_state);
private:
    std::optional<std::shared_ptr<WizardStateConsole> > state_;
};


#endif //SIMPLETASKMANAGER_CONSOLESTATEMACHINE_H
