//
// Created by Maksym Kharchenko on 02.12.2021.
//

#ifndef SIMPLETASKMANAGER_ADDSUBTASKSTATE_H
#define SIMPLETASKMANAGER_ADDSUBTASKSTATE_H

#include "states/StateInterface.h"
#include "states/factory/StatesFactory.h"
#include "user_interface/StateContext.h"

#include <memory>
#include <optional>

class AddSubTaskState : public StateInterface {
public:
    explicit AddSubTaskState(const std::shared_ptr<StatesFactory>& factory);
public:
    std::shared_ptr<StateInterface> Execute(StateContext& context) override;
private:
    std::weak_ptr<StatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_ADDSUBTASKSTATE_H
