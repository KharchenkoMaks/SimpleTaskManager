//
// Created by Maksym Kharchenko on 24.11.2021.
//

#ifndef SIMPLETASKMANAGER_ADDTASKSTATE_H
#define SIMPLETASKMANAGER_ADDTASKSTATE_H

#include "states/abstract/IWizardState.h"
#include "states/factory/WizardStatesFactory.h"
#include "WizardContext.h"
//#include "ConsoleStateMachine.h"

#include <memory>
#include <optional>

class AddTaskState : public IWizardState {
public:
    AddTaskState(const std::shared_ptr<WizardStatesFactory>& states_factory);
public:
    std::optional<std::shared_ptr<IWizardState>> Execute(std::shared_ptr<WizardContext> context) override;
};


#endif //SIMPLETASKMANAGER_ADDTASKSTATE_H
