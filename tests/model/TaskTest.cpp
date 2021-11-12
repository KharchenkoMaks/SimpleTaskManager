//
// Created by Maksym Kharchenko on 12.11.2021.
//

#include "gtest/gtest.h"
#include "../../src/model/Task.h"

#include <ctime>

class TaskTest : public ::testing::Test{

};

// Creating Task object with title "title"
// Task::GetTitle() should return "title"
TEST_F(TaskTest, creatingTaskWithTitle_shouldReturnInitialTitle){
    // Arrange
    std::string expected = "title";
    Task task = Task::Create(expected, Task::Priority::NONE, time(0));
    // Act
    std::string actual = task.GetTitle();
    // Assert
    EXPECT_EQ(expected, actual);
}

// Using Task::Create giving empty title
// Throws std::invalid_argument
TEST_F(TaskTest, creatingTaskWithEmpyTitle_shouldThrowInvalidArgument){
    EXPECT_THROW(Task::Create("", Task::Priority::NONE, time(0)), std::invalid_argument);
}

// Creating Task with Title = "title"
// Priority = HIGH and due_date = 1636739250
// Should return correct string
TEST_F(TaskTest, usingToStringTaskMethod_shouldReturnCorrectString){
    // Arrange
    time_t some_time = 1636739250;
    Task task = Task::Create("title", Task::Priority::HIGH, some_time);
    std::string expected = task.GetTitle() + ", Priority: High, Due to: 1636739250\n";
    // Act
    std::string actual = task.to_string();
    // Assert
    EXPECT_EQ(expected, actual);
}