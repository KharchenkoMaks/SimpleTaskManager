//
// Created by Maksym Kharchenko on 24.11.2021.
//

#ifndef SIMPLETASKMANAGER_ADDTASKSTATE_H
#define SIMPLETASKMANAGER_ADDTASKSTATE_H

#include "states/StateInterface.h"
#include "states/factory/StatesFactory.h"
#include "user_interface/StateContext.h"

#include <memory>
#include <optional>

class AddTaskState : public StateInterface {
public:
    explicit AddTaskState(const std::shared_ptr<StatesFactory>& factory);
public:
    std::shared_ptr<StateInterface> Execute(StateContext& context) override;
private:
    std::weak_ptr<StatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_ADDTASKSTATE_H
