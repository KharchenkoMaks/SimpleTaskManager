//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_QUITSTATE_H
#define SIMPLETASKMANAGER_QUITSTATE_H

#include "abstract/IWizardState.h"
#include "factory/WizardStatesFactory.h"
#include "WizardContext.h"

#include <memory>

class QuitState : public IWizardState {
public:
    std::shared_ptr<IWizardState> Execute(std::shared_ptr<WizardContext> context,
                                          std::shared_ptr<WizardStatesFactory> state_factory) override;
};


#endif //SIMPLETASKMANAGER_QUITSTATE_H
