//
// Created by Maksym Kharchenko on 16.12.2021.
//

#ifndef SIMPLETASKMANAGER_SAVESTATE_H
#define SIMPLETASKMANAGER_SAVESTATE_H

#include "states/StateInterface.h"
#include "states/factory/StatesFactory.h"
#include "StateContext.h"
#include "Task.pb.h"
#include "persistence/TasksPersistence.h"

#include <memory>
#include <optional>

class SaveState : public StateInterface {
public:
    explicit SaveState(const std::shared_ptr<StatesFactory>& factory);
public:
    std::shared_ptr<StateInterface> Execute(std::shared_ptr<StateContext> context) override;
private:
    std::weak_ptr<StatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_SAVESTATE_H