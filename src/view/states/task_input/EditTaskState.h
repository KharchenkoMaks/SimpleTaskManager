//
// Created by Maksym Kharchenko on 25.11.2021.
//

#ifndef SIMPLETASKMANAGER_EDITTASKSTATE_H
#define SIMPLETASKMANAGER_EDITTASKSTATE_H

#include "states/abstract/WizardStateInterface.h"
#include "states/factory/WizardStatesFactory.h"
#include "WizardContext.h"
#include "Task.pb.h"

#include <memory>
#include <optional>

class EditTaskState : public WizardStateInterface {
public:
    EditTaskState(const std::shared_ptr<WizardStatesFactory>& factory);
public:
    std::shared_ptr<WizardStateInterface> Execute(std::shared_ptr<WizardContext> context) override;
private:
    std::weak_ptr<WizardStatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_EDITTASKSTATE_H
