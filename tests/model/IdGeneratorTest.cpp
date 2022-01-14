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
    const int test_times = 100;
    IdGenerator generator;
    // Act & Assert
    for (int expected = 1; expected < test_times; ++expected){
        TaskId task = generator.CreateNewTaskId();
        EXPECT_EQ(task.id(), expected);
    }
}

TEST_F(IdGeneratorTest, SetLastTaskId_ShouldResetLastTaskId) {
    // Arrange
    const int test_times = 100;
    TaskId last_id;
    last_id.set_id(42);
    IdGenerator generator;
    // Act & Assert
    generator.SetLastTaskId(last_id);
    for (int expected = last_id.id() + 1; expected < test_times + last_id.id() + 1; ++expected){
        TaskId task = generator.CreateNewTaskId();
        EXPECT_EQ(task.id(), expected);
    }
}
