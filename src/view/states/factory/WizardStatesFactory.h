//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_WIZARDSTATESFACTORY_H
#define SIMPLETASKMANAGER_WIZARDSTATESFACTORY_H

#include "states/abstract/IWizardState.h"
#include "states/RootState.h"
#include "printer/ConsolePrinter.h"

#include <memory>
#include <string>

class WizardStatesFactory {
public:
    WizardStatesFactory();
    std::shared_ptr<IWizardState> CreateStateByCommand(const std::string& command);
    std::shared_ptr<RootState> CreateRootState();
private:
    std::shared_ptr<RootState> root_state_;
};


#endif //SIMPLETASKMANAGER_WIZARDSTATESFACTORY_H
