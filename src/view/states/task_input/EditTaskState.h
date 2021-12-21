//
// Created by Maksym Kharchenko on 25.11.2021.
//

#ifndef SIMPLETASKMANAGER_EDITTASKSTATE_H
#define SIMPLETASKMANAGER_EDITTASKSTATE_H

#include "states/StateInterface.h"
#include "states/factory/StatesFactory.h"
#include "StateContext.h"
#include "Task.pb.h"

#include <memory>
#include <optional>

class EditTaskState : public StateInterface {
public:
    EditTaskState(const std::shared_ptr<StatesFactory>& factory);
public:
    std::shared_ptr<StateInterface> Execute(std::shared_ptr<StateContext> context) override;
private:
    std::weak_ptr<StatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_EDITTASKSTATE_H
