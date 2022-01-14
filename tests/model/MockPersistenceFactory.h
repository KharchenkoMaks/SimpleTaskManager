//
// Created by Maksym Kharchenko on 14.01.2022.
//

#ifndef SIMPLETASKMANAGER_MOCKPERSISTENCEFACTORY_H
#define SIMPLETASKMANAGER_MOCKPERSISTENCEFACTORY_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "persistence/PersistenceFactory.h"

class MockPersistenceFactory : public persistence::PersistenceFactory {
public:
    MOCK_METHOD(std::unique_ptr<persistence::Persistence>, CreateFilePersistence, (const std::string& file_name), (override));
};

#endif //SIMPLETASKMANAGER_MOCKPERSISTENCEFACTORY_H
