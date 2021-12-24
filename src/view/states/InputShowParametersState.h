//
// Created by Maksym Kharchenko on 30.11.2021.
//

#ifndef SIMPLETASKMANAGER_INPUTSHOWPARAMETERSSTATE_H
#define SIMPLETASKMANAGER_INPUTSHOWPARAMETERSSTATE_H

#include "StateInterface.h"
#include "states/factory/StatesFactory.h"
#include "user_interface/StateContext.h"
#include "Task.pb.h"

#include <memory>
#include <optional>

class InputShowParametersState : public StateInterface {
public:
    explicit InputShowParametersState(const std::shared_ptr<StatesFactory>& factory);
public:
    std::shared_ptr<StateInterface> Execute(StateContext& context) override;
private:
    std::weak_ptr<StatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_INPUTSHOWPARAMETERSSTATE_H
