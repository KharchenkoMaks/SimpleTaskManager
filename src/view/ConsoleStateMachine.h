//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_CONSOLESTATEMACHINE_H
#define SIMPLETASKMANAGER_CONSOLESTATEMACHINE_H

#include "WizardContext.h"
#include "states/IWizardState.h"

#include <memory>

class ConsoleStateMachine {
public:
    void Run();
private:
    std::shared_ptr<WizardContext> context_;
    std::shared_ptr<IWizardState> state_;
};


#endif //SIMPLETASKMANAGER_CONSOLESTATEMACHINE_H