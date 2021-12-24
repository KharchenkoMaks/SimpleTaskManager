//
// Created by Maksym Kharchenko on 09.12.2021.
//

#ifndef SIMPLETASKMANAGER_ENDSTATE_H
#define SIMPLETASKMANAGER_ENDSTATE_H

#include "StateInterface.h"
#include "states/factory/StatesFactory.h"
#include "user_interface/StateContext.h"

#include <memory>
#include <string>

class EndState : public StateInterface {
public:
    EndState(const std::shared_ptr<StatesFactory>& factory);
public:
    std::shared_ptr<StateInterface> Execute(StateContext& context) override;
private:
    std::weak_ptr<StatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_ENDSTATE_H
