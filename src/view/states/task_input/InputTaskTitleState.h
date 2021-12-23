//
// Created by Maksym Kharchenko on 24.11.2021.
//

#ifndef SIMPLETASKMANAGER_INPUTTASKTITLESTATE_H
#define SIMPLETASKMANAGER_INPUTTASKTITLESTATE_H

#include "states/StateInterface.h"
#include "states/factory/StatesFactory.h"
#include "user_interface/StateContext.h"

#include <string>
#include <memory>

class InputTaskTitleState : public StateInterface {
public:
    explicit InputTaskTitleState(const std::shared_ptr<StatesFactory>& factory);
public:
    std::shared_ptr<StateInterface> Execute(std::shared_ptr<StateContext> context) override;
public:
    std::string GetUserInputForTitleAdd();
    std::string GetUserInputForTitleEdit(const Task& task);
private:
    std::weak_ptr<StatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_INPUTTASKTITLESTATE_H
