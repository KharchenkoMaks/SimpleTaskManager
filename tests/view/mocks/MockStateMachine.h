//
// Created by Maksym Kharchenko on 07.12.2021.
//

#ifndef SIMPLETASKMANAGER_MOCKSTATEMACHINE_H
#define SIMPLETASKMANAGER_MOCKSTATEMACHINE_H

#include "user_interface/ConsoleStateMachine.h"

class MockStateMachine : public ConsoleStateMachine {
public:
    MockStateMachine() : ConsoleStateMachine(nullptr, nullptr) {}

    MOCK_METHOD(std::shared_ptr<StateContext>, Run, (), (override));
};

#endif //SIMPLETASKMANAGER_MOCKSTATEMACHINE_H
