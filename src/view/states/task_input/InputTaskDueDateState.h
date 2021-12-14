//
// Created by Maksym Kharchenko on 24.11.2021.
//

#ifndef SIMPLETASKMANAGER_INPUTTASKDUEDATESTATE_H
#define SIMPLETASKMANAGER_INPUTTASKDUEDATESTATE_H

#include "states/abstract/WizardStateInterface.h"
#include "states/factory/WizardStatesFactory.h"
#include "states/abstract/StateDependencies.h"
#include "WizardContext.h"
#include "utilities/DueDateUtilities.h"

#include <string>
#include <memory>
#include <ctime>
#include <optional>

class InputTaskDueDateState : public WizardStateInterface {
public:
    InputTaskDueDateState(std::unique_ptr<StateDependencies> dependencies);
public:
    std::shared_ptr<WizardStateInterface> Execute(std::shared_ptr<WizardContext> context) override;
private:
    std::string GetUserInputForDueDateAdd();
    std::string GetUserInputForDueDateEdit(const Task& task);
private:
    std::unique_ptr<StateDependencies> dependencies_;
};


#endif //SIMPLETASKMANAGER_INPUTTASKDUEDATESTATE_H
