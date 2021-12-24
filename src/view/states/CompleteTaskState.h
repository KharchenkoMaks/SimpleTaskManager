//
// Created by Maksym Kharchenko on 01.12.2021.
//

#ifndef SIMPLETASKMANAGER_COMPLETETASKSTATE_H
#define SIMPLETASKMANAGER_COMPLETETASKSTATE_H

#include "StateInterface.h"
#include "states/factory/StatesFactory.h"
#include "user_interface/StateContext.h"
#include "Task.pb.h"
#include "utilities/TaskActionResult.h"

#include <memory>
#include <optional>

class CompleteTaskState : public StateInterface {
public:
    explicit CompleteTaskState(const std::shared_ptr<StatesFactory>& factory);
public:
    std::shared_ptr<StateInterface> Execute(StateContext& context) override;
private:
    std::weak_ptr<StatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_COMPLETETASKSTATE_H
