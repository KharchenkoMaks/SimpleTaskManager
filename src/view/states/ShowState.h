//
// Created by Maksym Kharchenko on 30.11.2021.
//

#ifndef SIMPLETASKMANAGER_SHOWSTATE_H
#define SIMPLETASKMANAGER_SHOWSTATE_H

#include "states/abstract/WizardStateInterface.h"
#include "states/factory/WizardStatesFactory.h"
#include "states/abstract/StateDependencies.h"
#include "WizardContext.h"
#include "Task.pb.h"

#include <memory>
#include <optional>

class ShowState : public WizardStateInterface {
public:
    explicit ShowState(std::unique_ptr<StateDependencies> dependencies);
public:
    std::shared_ptr<WizardStateInterface> Execute(std::shared_ptr<WizardContext> context) override;
private:
    void PrintTasks(const std::vector<TaskTransfer>& tasks);
private:
    std::unique_ptr<StateDependencies> dependencies_;
};


#endif //SIMPLETASKMANAGER_SHOWSTATE_H
