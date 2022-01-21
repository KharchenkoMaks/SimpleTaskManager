//
// Created by Maksym Kharchenko on 30.11.2021.
//

#ifndef SIMPLETASKMANAGER_INPUTSHOWPARAMETERSSTATE_H
#define SIMPLETASKMANAGER_INPUTSHOWPARAMETERSSTATE_H

#include "State.h"
#include "states/factory/StatesFactory.h"
#include "user_interface/StateContext.h"
#include "Task.pb.h"

#include <memory>
#include <optional>

class InputShowParametersState : public State {
public:
    explicit InputShowParametersState(const std::shared_ptr<StatesFactory>& factory);
public:
    std::shared_ptr<State> Execute(StateContext& context) override;
private:
    std::shared_ptr<StatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_INPUTSHOWPARAMETERSSTATE_H
