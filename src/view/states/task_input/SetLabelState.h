//
// Created by Maksym Kharchenko on 06.12.2021.
//

#ifndef SIMPLETASKMANAGER_SETLABELSTATE_H
#define SIMPLETASKMANAGER_SETLABELSTATE_H

#include "states/State.h"
#include "states/factory/StatesFactory.h"
#include "user_interface/StateContext.h"

#include <memory>
#include <optional>

class SetLabelState : public State {
public:
    explicit SetLabelState(const std::shared_ptr<StatesFactory>& factory);
public:
    std::shared_ptr<State> Execute(StateContext& context) override;
private:
    std::weak_ptr<StatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_SETLABELSTATE_H
