//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_ROOTSTATE_H
#define SIMPLETASKMANAGER_ROOTSTATE_H

#include "abstract/WizardStateInterface.h"
#include "states/factory/WizardStatesFactory.h"
#include "abstract/StateDependencies.h"
#include "WizardContext.h"

#include <string>
#include <memory>

class RootState : public WizardStateInterface {
public:
    explicit RootState(std::unique_ptr<StateDependencies> dependencies);
public:
    std::shared_ptr<WizardStateInterface> Execute(std::shared_ptr<WizardContext> context) override;
private:
    std::unique_ptr<StateDependencies> dependencies_;
};


#endif //SIMPLETASKMANAGER_ROOTSTATE_H
