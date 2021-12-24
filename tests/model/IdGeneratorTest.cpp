//
// Created by Maksym Kharchenko on 13.11.2021.
//

#include "gtest/gtest.h"
#include "IdGenerator.h"
#include "Task.pb.h"

class IdGeneratorTest : public ::testing::Test{

};

// Creating new TaskIds using IdGenerator
// Should return incremented TaskId
TEST_F(IdGeneratorTest, CreateNewTaskId_shouldIncrementTaskId){
    // Arrange
    const int test_times = 5;
    IdGenerator generator;
    // Act & Assert
    for (int expected = 0; expected < test_times; ++expected){
        TaskId task = generator.CreateNewTaskId();
        EXPECT_EQ(task.id(), expected);
    }
}

// Initializing IdGenerator with custom last_id
// Should increment TaskId starting from given last_id
TEST_F(IdGeneratorTest, InitializeIdGenerator_shouldIncrementTaskIdFromLastId){
    // Arrange
    const int last_id = 20;
    const int test_times = 5;
    IdGenerator generator(last_id);
    // Act & Assert
    for (int expected = last_id; expected < last_id + test_times; ++expected){
        TaskId task = generator.CreateNewTaskId();
        EXPECT_EQ(task.id(), expected);
    }
}

// Initializing IdGenerator with negative last_id
// Should throw std::invalid_argument
TEST_F(IdGeneratorTest, InitializeIdGeneratorWithNegativeLastId_shouldThrowInvalidArgument){
    EXPECT_THROW(IdGenerator generator(-4), std::invalid_argument);
}