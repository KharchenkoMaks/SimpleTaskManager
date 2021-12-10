//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_HELPSTATE_H
#define SIMPLETASKMANAGER_HELPSTATE_H

#include "abstract/WizardStateInterface.h"
#include "states/factory/WizardStatesFactory.h"
#include "abstract/StateDependencies.h"

#include <string>
#include <memory>

class HelpState : public WizardStateInterface {
public:
    explicit HelpState(std::unique_ptr<StateDependencies> dependencies);
public:
    std::shared_ptr<WizardStateInterface> Execute(std::shared_ptr<WizardContext> context) override;
private:
    std::unique_ptr<StateDependencies> dependencies_;
};


#endif //SIMPLETASKMANAGER_HELPSTATE_H
