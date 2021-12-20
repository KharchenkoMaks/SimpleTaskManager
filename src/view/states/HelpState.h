//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_HELPSTATE_H
#define SIMPLETASKMANAGER_HELPSTATE_H

#include "abstract/WizardStateInterface.h"
#include "states/factory/WizardStatesFactory.h"

#include <string>
#include <memory>

class HelpState : public WizardStateInterface {
public:
    explicit HelpState(const std::shared_ptr<WizardStatesFactory>& factory);
public:
    std::shared_ptr<WizardStateInterface> Execute(std::shared_ptr<WizardContext> context) override;
private:
    std::weak_ptr<WizardStatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_HELPSTATE_H
