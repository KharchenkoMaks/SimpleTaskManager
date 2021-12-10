//
// Created by Maksym Kharchenko on 24.11.2021.
//

#ifndef SIMPLETASKMANAGER_INPUTTASKPRIORITYSTATE_H
#define SIMPLETASKMANAGER_INPUTTASKPRIORITYSTATE_H

#include "states/abstract/WizardStateInterface.h"
#include "states/factory/WizardStatesFactory.h"
#include "states/abstract/StateDependencies.h"
#include "WizardContext.h"

#include <string>
#include <memory>

class InputTaskPriorityState : public WizardStateInterface {
public:
    explicit InputTaskPriorityState(std::unique_ptr<StateDependencies> dependencies);
public:
    std::shared_ptr<WizardStateInterface> Execute(std::shared_ptr<WizardContext> context) override;
private:
    std::string GetUserInputForPriorityAdd();
    std::string GetUserInputForPriorityEdit(const Task& task);
private:
    std::unique_ptr<StateDependencies> dependencies_;
};


#endif //SIMPLETASKMANAGER_INPUTTASKPRIORITYSTATE_H
