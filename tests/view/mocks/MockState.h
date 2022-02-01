//
// Created by Maksym Kharchenko on 13.01.2022.
//

#ifndef SIMPLETASKMANAGER_MOCKSTATE_H
#define SIMPLETASKMANAGER_MOCKSTATE_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "view/states/State.h"

class MockState : public State {
public:
    MOCK_METHOD(StateType, Execute, (StateContext&), (override));
};

#endif //SIMPLETASKMANAGER_MOCKSTATE_H
