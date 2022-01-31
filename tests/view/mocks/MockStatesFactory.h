//
// Created by Maksym Kharchenko on 03.12.2021.
//

#ifndef SIMPLETASKMANAGER_MOCKSTATESFACTORY_H
#define SIMPLETASKMANAGER_MOCKSTATESFACTORY_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "states/factory/StatesFactory.h"

class MockStatesFactory : public StatesFactory {
public:
    MOCK_METHOD(std::shared_ptr<State>, GetState, (StateType state), (override));
};

#endif //SIMPLETASKMANAGER_MOCKSTATESFACTORY_H
