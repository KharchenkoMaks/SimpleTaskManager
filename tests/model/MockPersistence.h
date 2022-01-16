//
// Created by Maksym Kharchenko on 16.01.2022.
//

#ifndef SIMPLETASKMANAGER_MOCKPERSISTENCE_H
#define SIMPLETASKMANAGER_MOCKPERSISTENCE_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "persistence/Persistence.h"

class MockPersistence : public persistence::Persistence {
public:
    MOCK_METHOD((std::pair<persistence::SaveLoadStatus, std::vector<TaskTransfer>>), Load, (), (override));
    MOCK_METHOD(persistence::SaveLoadStatus, Save, (const std::vector<TaskTransfer> &tasks), (override));
};

#endif //SIMPLETASKMANAGER_MOCKPERSISTENCE_H
