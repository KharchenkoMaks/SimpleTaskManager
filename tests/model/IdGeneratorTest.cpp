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
