//
// Created by Maksym Kharchenko on 02.12.2021.
//

#ifndef SIMPLETASKMANAGER_DELETETASKSTATE_H
#define SIMPLETASKMANAGER_DELETETASKSTATE_H

#include "states/abstract/WizardStateInterface.h"
#include "states/factory/WizardStatesFactory.h"
#include "states/abstract/StateDependencies.h"
#include "WizardContext.h"
#include "tasks/Task.h"
#include "id/TaskId.h"

#include <memory>
#include <optional>

class DeleteTaskState : public WizardStateInterface {
public:
    DeleteTaskState(std::unique_ptr<StateDependencies> dependencies);
public:
    std::shared_ptr<WizardStateInterface> Execute(std::shared_ptr<WizardContext> context) override;
private:
    std::unique_ptr<StateDependencies> dependencies_;
};


#endif //SIMPLETASKMANAGER_DELETETASKSTATE_H
