//
// Created by Maksym Kharchenko on 16.12.2021.
//

#ifndef SIMPLETASKMANAGER_LOADSTATE_H
#define SIMPLETASKMANAGER_LOADSTATE_H

#include "states/abstract/WizardStateInterface.h"
#include "states/factory/WizardStatesFactory.h"
#include "states/abstract/StateDependencies.h"
#include "WizardContext.h"
#include "Task.pb.h"
#include "persistence/TasksPersistence.h"

#include <memory>
#include <optional>

class LoadState : public WizardStateInterface {
public:
    explicit LoadState(std::unique_ptr<StateDependencies> dependencies);
public:
    std::shared_ptr<WizardStateInterface> Execute(std::shared_ptr<WizardContext> context) override;
private:
    std::unique_ptr<StateDependencies> dependencies_;
};


#endif //SIMPLETASKMANAGER_LOADSTATE_H
