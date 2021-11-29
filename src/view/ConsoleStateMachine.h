//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_CONSOLESTATEMACHINE_H
#define SIMPLETASKMANAGER_CONSOLESTATEMACHINE_H

#include "states/factory/WizardStatesFactory.h"
#include "WizardContext.h"
#include "states/abstract/IWizardState.h"

#include <memory>
#include <optional>

class ConsoleStateMachine {
public:
    ConsoleStateMachine(const std::optional<std::shared_ptr<IWizardState>>& initial_state);
public:
    // Returns context after running end
    std::shared_ptr<WizardContext> Run();
private:
    std::shared_ptr<WizardContext> context_;
    std::optional<std::shared_ptr<IWizardState> > state_;
};


#endif //SIMPLETASKMANAGER_CONSOLESTATEMACHINE_H
