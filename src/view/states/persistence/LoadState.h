//
// Created by Maksym Kharchenko on 16.12.2021.
//

#ifndef SIMPLETASKMANAGER_LOADSTATE_H
#define SIMPLETASKMANAGER_LOADSTATE_H

#include "states/State.h"
#include "states/factory/StatesFactory.h"
#include "user_interface/StateContext.h"
#include "Task.pb.h"
#include "persistence/FilePersistence.h"

#include <memory>
#include <optional>

class LoadState : public State {
public:
    explicit LoadState(const std::shared_ptr<StatesFactory>& factory);
public:
    std::shared_ptr<State> Execute(StateContext& context) override;
private:
    std::weak_ptr<StatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_LOADSTATE_H
