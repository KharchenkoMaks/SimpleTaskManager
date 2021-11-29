//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_IWIZARDSTATE_H
#define SIMPLETASKMANAGER_IWIZARDSTATE_H

#include "WizardContext.h"
//#include "states/factory/WizardStatesFactory.h"

#include <memory>
#include <optional>

class WizardStatesFactory;

class IWizardState {
public:
    explicit IWizardState(const std::shared_ptr<WizardStatesFactory>& states_factory);
public:
    virtual std::optional<std::shared_ptr<IWizardState>> Execute(std::shared_ptr<WizardContext>) = 0;

    std::shared_ptr<WizardStatesFactory> GetFactory();
public:
    virtual ~IWizardState() = default;
private:
    std::shared_ptr<WizardStatesFactory> states_factory_;
};


#endif //SIMPLETASKMANAGER_IWIZARDSTATE_H
