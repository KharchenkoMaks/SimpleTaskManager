//
// Created by Maksym Kharchenko on 24.11.2021.
//

#ifndef SIMPLETASKMANAGER_INPUTTASKTITLESTATE_H
#define SIMPLETASKMANAGER_INPUTTASKTITLESTATE_H

#include "states/State.h"
#include "states/factory/StatesFactory.h"
#include "user_interface/StateContext.h"

#include <string>
#include <memory>

class InputTaskTitleState : public State {
public:
    explicit InputTaskTitleState(const std::shared_ptr<StatesFactory>& factory);
public:
    std::shared_ptr<State> Execute(StateContext& context) override;
private:
    std::weak_ptr<StatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_INPUTTASKTITLESTATE_H
