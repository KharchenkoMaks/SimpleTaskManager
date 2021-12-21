//
// Created by Maksym Kharchenko on 06.12.2021.
//

#ifndef SIMPLETASKMANAGER_SETLABELSTATE_H
#define SIMPLETASKMANAGER_SETLABELSTATE_H

#include "states/StateInterface.h"
#include "states/factory/StatesFactory.h"
#include "StateContext.h"

#include <memory>
#include <optional>

class SetLabelState : public StateInterface {
public:
    SetLabelState(const std::shared_ptr<StatesFactory>& factory);
public:
    std::shared_ptr<StateInterface> Execute(std::shared_ptr<StateContext> context) override;
private:
    std::weak_ptr<StatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_SETLABELSTATE_H
