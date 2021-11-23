//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_IWIZARDSTATE_H
#define SIMPLETASKMANAGER_IWIZARDSTATE_H

#include "WizardContext.h"

#include <memory>

class IWizardState {
public:
    virtual std::shared_ptr<IWizardState> Execute(std::shared_ptr<WizardContext>) = 0;

    virtual ~IWizardState() = default;
};


#endif //SIMPLETASKMANAGER_IWIZARDSTATE_H
