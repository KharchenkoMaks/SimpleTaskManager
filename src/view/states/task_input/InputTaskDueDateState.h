//
// Created by Maksym Kharchenko on 24.11.2021.
//

#ifndef SIMPLETASKMANAGER_INPUTTASKDUEDATESTATE_H
#define SIMPLETASKMANAGER_INPUTTASKDUEDATESTATE_H

#include "states/StateInterface.h"
#include "states/factory/StatesFactory.h"
#include "user_interface/StateContext.h"

#include <string>
#include <memory>
#include <ctime>
#include <optional>

class InputTaskDueDateState : public StateInterface {
public:
    InputTaskDueDateState(const std::shared_ptr<StatesFactory>& factory);
public:
    std::shared_ptr<StateInterface> Execute(StateContext& context) override;
private:
    std::string GetUserInputForDueDateAdd();
private:
    std::weak_ptr<StatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_INPUTTASKDUEDATESTATE_H
