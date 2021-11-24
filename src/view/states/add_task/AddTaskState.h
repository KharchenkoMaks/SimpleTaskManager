//
// Created by Maksym Kharchenko on 24.11.2021.
//

#ifndef SIMPLETASKMANAGER_ADDTASKSTATE_H
#define SIMPLETASKMANAGER_ADDTASKSTATE_H

#include "states/abstract/IWizardState.h"
#include "states/factory/WizardStatesFactory.h"
#include "context/WizardContext.h"

#include <memory>

class AddTaskState : public IWizardState {
public:
    std::shared_ptr<IWizardState> Execute(std::shared_ptr<WizardContext> context,
                                          std::shared_ptr<WizardStatesFactory> state_factory) override;
};


#endif //SIMPLETASKMANAGER_ADDTASKSTATE_H
