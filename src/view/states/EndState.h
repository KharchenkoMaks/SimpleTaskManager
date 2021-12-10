//
// Created by Maksym Kharchenko on 09.12.2021.
//

#ifndef SIMPLETASKMANAGER_ENDSTATE_H
#define SIMPLETASKMANAGER_ENDSTATE_H

#include "states/abstract/WizardStateInterface.h"
#include "states/factory/WizardStatesFactory.h"
#include "states/abstract/StateDependencies.h"
#include "WizardContext.h"

#include <memory>
#include <string>

class EndState : public WizardStateInterface {
public:
    EndState(std::unique_ptr<StateDependencies> dependencies);
public:
    std::shared_ptr<WizardStateInterface> Execute(std::shared_ptr<WizardContext> context) override;
private:
    std::unique_ptr<StateDependencies> dependencies_;
};


#endif //SIMPLETASKMANAGER_ENDSTATE_H
