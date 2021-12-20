//
// Created by Maksym Kharchenko on 24.11.2021.
//

#ifndef SIMPLETASKMANAGER_INPUTTASKTITLESTATE_H
#define SIMPLETASKMANAGER_INPUTTASKTITLESTATE_H

#include "states/abstract/WizardStateInterface.h"
#include "states/factory/WizardStatesFactory.h"
#include "WizardContext.h"

#include <string>
#include <memory>

class InputTaskTitleState : public WizardStateInterface {
public:
    explicit InputTaskTitleState(const std::shared_ptr<WizardStatesFactory>& factory);
public:
    std::shared_ptr<WizardStateInterface> Execute(std::shared_ptr<WizardContext> context) override;
public:
    std::string GetUserInputForTitleAdd();
    std::string GetUserInputForTitleEdit(const Task& task);
private:
    std::weak_ptr<WizardStatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_INPUTTASKTITLESTATE_H
