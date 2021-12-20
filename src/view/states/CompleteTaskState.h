//
// Created by Maksym Kharchenko on 01.12.2021.
//

#ifndef SIMPLETASKMANAGER_COMPLETETASKSTATE_H
#define SIMPLETASKMANAGER_COMPLETETASKSTATE_H

#include "states/abstract/WizardStateInterface.h"
#include "states/factory/WizardStatesFactory.h"
#include "WizardContext.h"
#include "Task.pb.h"
#include "utilities/TaskActionResult.h"

#include <memory>
#include <optional>

class CompleteTaskState : public WizardStateInterface {
public:
    CompleteTaskState(const std::shared_ptr<WizardStatesFactory>& factory);
public:
    std::shared_ptr<WizardStateInterface> Execute(std::shared_ptr<WizardContext> context) override;
private:
    std::weak_ptr<WizardStatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_COMPLETETASKSTATE_H
