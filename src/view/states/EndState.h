//
// Created by Maksym Kharchenko on 09.12.2021.
//

#ifndef SIMPLETASKMANAGER_ENDSTATE_H
#define SIMPLETASKMANAGER_ENDSTATE_H

#include "states/abstract/WizardStateInterface.h"
#include "states/factory/WizardStatesFactory.h"
#include "WizardContext.h"

#include <memory>
#include <string>

class EndState : public WizardStateInterface {
public:
    EndState(const std::shared_ptr<WizardStatesFactory>& factory);
public:
    std::shared_ptr<WizardStateInterface> Execute(std::shared_ptr<WizardContext> context) override;
private:
    std::weak_ptr<WizardStatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_ENDSTATE_H
