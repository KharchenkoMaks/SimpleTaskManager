//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_HELPSTATE_H
#define SIMPLETASKMANAGER_HELPSTATE_H

#include "StateInterface.h"
#include "states/factory/StatesFactory.h"

#include <string>
#include <memory>

class HelpState : public StateInterface {
public:
    explicit HelpState(const std::shared_ptr<StatesFactory>& factory);
public:
    std::shared_ptr<StateInterface> Execute(std::shared_ptr<StateContext> context) override;
private:
    std::weak_ptr<StatesFactory> factory_;
};


#endif //SIMPLETASKMANAGER_HELPSTATE_H
