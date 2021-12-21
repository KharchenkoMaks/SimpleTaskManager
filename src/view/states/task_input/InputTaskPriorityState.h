//
// Created by Maksym Kharchenko on 24.11.2021.
//

#ifndef SIMPLETASKMANAGER_INPUTTASKPRIORITYSTATE_H
#define SIMPLETASKMANAGER_INPUTTASKPRIORITYSTATE_H

#include "states/StateInterface.h"
#include "states/factory/StatesFactory.h"
#include "StateContext.h"

#include <string>
#include <memory>

class InputTaskPriorityState : public StateInterface {
public:
    explicit InputTaskPriorityState(const std::shared_ptr<StatesFactory>& factory);
public:
    std::shared_ptr<StateInterface> Execute(std::shared_ptr<StateContext> context) override;
private:
    std::string GetUserInputForPriorityAdd();
    std::string GetUserInputForPriorityEdit(const Task& task);
private:
    std::weak_ptr<StatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_INPUTTASKPRIORITYSTATE_H
