//
// Created by Maksym Kharchenko on 02.12.2021.
//

#ifndef SIMPLETASKMANAGER_DELETETASKSTATE_H
#define SIMPLETASKMANAGER_DELETETASKSTATE_H

#include "StateInterface.h"
#include "states/factory/StatesFactory.h"
#include "StateContext.h"
#include "Task.pb.h"

#include <memory>
#include <optional>

class DeleteTaskState : public StateInterface {
public:
    DeleteTaskState(const std::shared_ptr<StatesFactory>& factory);
public:
    std::shared_ptr<StateInterface> Execute(std::shared_ptr<StateContext> context) override;
private:
    std::weak_ptr<StatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_DELETETASKSTATE_H
