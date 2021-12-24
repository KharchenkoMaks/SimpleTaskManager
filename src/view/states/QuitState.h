//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_QUITSTATE_H
#define SIMPLETASKMANAGER_QUITSTATE_H

#include "StateInterface.h"
#include "states/factory/StatesFactory.h"
#include "user_interface/StateContext.h"

#include <memory>
#include <string>

class QuitState : public StateInterface {
public:
    QuitState(const std::shared_ptr<StatesFactory>& factory);
public:
    std::shared_ptr<StateInterface> Execute(StateContext& context) override;
private:
    std::weak_ptr<StatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_QUITSTATE_H
