//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_STATESFACTORY_H
#define SIMPLETASKMANAGER_STATESFACTORY_H

#include "states/State.h"

#include <memory>

class StatesFactory {
public:
    virtual std::shared_ptr<State> GetState(StateType state) = 0;
public:
    virtual ~StatesFactory() = default;
};


#endif //SIMPLETASKMANAGER_STATESFACTORY_H
