//
// Created by Maksym Kharchenko on 13.11.2021.
//

#include "gtest/gtest.h"
#include "id/TaskId.h"

class TaskIdTest : public ::testing::Test{
protected:
    // TaskId::AddTask(10)
    const TaskId task1 = TaskId::Create(10);
    // TaskId::AddTask("10")
    const TaskId task2 = TaskId::Create("10");
    // TaskId::AddTask(5)
    const TaskId task3 = TaskId::Create(5);
};

// Creating task using int and string AddTask methods
TEST_F(TaskIdTest, TaskIdCreate_shouldCreateTaskWithRightId){
    // Arrange
    int expected = 10;
    TaskId task1 = TaskId::Create(expected);
    TaskId task2 = TaskId::Create(std::to_string(expected));
    // Act
    int actual1 = task1.GetId();
    int actual2 = task2.GetId();
    // Assert
    // Assert for TaskId::AddTask(int)
    EXPECT_EQ(expected, actual1);
    // Assert for TaskId::AddTask(std::string)
    EXPECT_EQ(expected, actual2);
}

// Creating task with negative id
// Should throw invalid_argument
TEST_F(TaskIdTest, TaskIdCreateWithIdUnderZero_throwInvalidArgument){
    EXPECT_THROW(TaskId::Create(-5), std::invalid_argument);
    EXPECT_THROW(TaskId::Create("-6"), std::invalid_argument);
}

// Creating task giving incorrect id string
// Should throw invalid_argument
TEST_F(TaskIdTest, TaskIdCreateWithIncorrectString_throwInvalidArgument){
    EXPECT_THROW(TaskId::Create("asf"), std::invalid_argument);
}

// Using operator== to check objects for equality
TEST_F(TaskIdTest, TaskIdOperatorEquals_shouldCheckObjectsForEquality){
    // Act & Assert
    EXPECT_TRUE(task1 == task2);
    EXPECT_FALSE(task1 == task3);
    EXPECT_FALSE(task2 == task3);
}

// Using operator< for different objects
TEST_F(TaskIdTest, TaskIdOperatorLess_ComparesObjectsCorrectly){
    // Act & Assert
    EXPECT_TRUE(task3 < task1);
    EXPECT_TRUE(task3 < task2);
    EXPECT_FALSE(task1 < task3);
    EXPECT_FALSE(task1 < task2);
    EXPECT_FALSE(task2 < task1);
}
