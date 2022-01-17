//
// Created by Maksym Kharchenko on 17.01.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "persistence/PersistenceFactory.h"

#include "persistence/Persistence.h"

#include "persistence/FilePersistence.h"

#include <typeinfo>

class PersistenceFactoryTests : public ::testing::Test {
public:
    template<class TExpected>
    void TestPersistenceType(const persistence::Persistence& actual_persistence) {
        EXPECT_EQ(typeid(TExpected), typeid(actual_persistence));
    }
};

TEST_F(PersistenceFactoryTests, CreateFilePersistence_ShouldCreateFilePersistence) {
    // Arrange
    persistence::PersistenceFactory factory;
    const std::string expected_file_name = "some_file";
    // Act
    std::unique_ptr<persistence::Persistence> actual_persistence = factory.CreateFilePersistence(expected_file_name);
    // Assert
    TestPersistenceType<persistence::FilePersistence>(*actual_persistence);
}
