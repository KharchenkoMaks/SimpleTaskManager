//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_CONSOLESTATEMACHINE_H
#define SIMPLETASKMANAGER_CONSOLESTATEMACHINE_H

#include "context/WizardContext.h"
#include "states/abstract/IWizardState.h"
#include "states/factory/WizardStatesFactory.h"

#include <memory>

class ConsoleStateMachine {
public:
    // Returns context after running end
    WizardContext Run(WizardStatesFactory::States initial_state);
private:
    std::shared_ptr<WizardContext> context_;
    std::shared_ptr<IWizardState> state_;
};


#endif //SIMPLETASKMANAGER_CONSOLESTATEMACHINE_H
