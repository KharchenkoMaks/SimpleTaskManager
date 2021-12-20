//
// Created by Maksym Kharchenko on 16.12.2021.
//

#ifndef SIMPLETASKMANAGER_SAVESTATE_H
#define SIMPLETASKMANAGER_SAVESTATE_H

#include "states/abstract/WizardStateInterface.h"
#include "states/factory/WizardStatesFactory.h"
#include "WizardContext.h"
#include "Task.pb.h"
#include "persistence/TasksPersistence.h"

#include <memory>
#include <optional>

class SaveState : public WizardStateInterface {
public:
    explicit SaveState(const std::shared_ptr<WizardStatesFactory>& factory);
public:
    std::shared_ptr<WizardStateInterface> Execute(std::shared_ptr<WizardContext> context) override;
private:
    std::weak_ptr<WizardStatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_SAVESTATE_H
