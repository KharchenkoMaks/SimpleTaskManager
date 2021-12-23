//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_ROOTSTATE_H
#define SIMPLETASKMANAGER_ROOTSTATE_H

#include "StateInterface.h"
#include "states/factory/StatesFactory.h"
#include "user_interface/StateContext.h"

#include <string>
#include <memory>

class RootState : public StateInterface {
public:
    RootState(const std::shared_ptr<StatesFactory>& factory);
public:
    std::shared_ptr<StateInterface> Execute(std::shared_ptr<StateContext> context) override;
private:
    std::weak_ptr<StatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_ROOTSTATE_H
