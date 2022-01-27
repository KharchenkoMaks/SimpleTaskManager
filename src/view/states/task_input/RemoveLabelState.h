//
// Created by Maksym Kharchenko on 17.01.2022.
//

#ifndef SIMPLETASKMANAGER_REMOVELABELSTATE_H
#define SIMPLETASKMANAGER_REMOVELABELSTATE_H

#include "states/State.h"
#include "states/factory/StatesFactory.h"
#include "user_interface/StateContext.h"

#include <memory>
#include <optional>

class RemoveLabelState : public State {
public:
    explicit RemoveLabelState(const std::shared_ptr<StatesFactory>& factory);
public:
    std::shared_ptr<State> Execute(StateContext& context) override;
private:
    std::weak_ptr<StatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_REMOVELABELSTATE_H
