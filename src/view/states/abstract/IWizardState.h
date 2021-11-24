//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_IWIZARDSTATE_H
#define SIMPLETASKMANAGER_IWIZARDSTATE_H

#include "context/WizardContext.h"
//#include "states/factory/WizardStatesFactory.h"

#include <memory>

class WizardStatesFactory;

class IWizardState {
public:
    virtual std::shared_ptr<IWizardState> Execute(std::shared_ptr<WizardContext>,
            std::shared_ptr<WizardStatesFactory>) = 0;

    virtual ~IWizardState() = default;
};


#endif //SIMPLETASKMANAGER_IWIZARDSTATE_H
