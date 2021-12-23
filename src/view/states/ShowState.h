//
// Created by Maksym Kharchenko on 30.11.2021.
//

#ifndef SIMPLETASKMANAGER_SHOWSTATE_H
#define SIMPLETASKMANAGER_SHOWSTATE_H

#include "StateInterface.h"
#include "states/factory/StatesFactory.h"
#include "user_interface/StateContext.h"
#include "Task.pb.h"

#include <memory>
#include <optional>

class ShowState : public StateInterface {
public:
    explicit ShowState(const std::shared_ptr<StatesFactory>& factory);
public:
    std::shared_ptr<StateInterface> Execute(std::shared_ptr<StateContext> context) override;
private:
    void PrintTasks(const std::vector<TaskTransfer>& tasks);
private:
    std::weak_ptr<StatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_SHOWSTATE_H
