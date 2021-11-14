//
// Created by Maksym Kharchenko on 12.11.2021.
//

#include "gtest/gtest.h"
#include "../../src/model/Task.h"

#include <ctime>
#include <vector>

class TaskTest : public ::testing::Test{

};

// Creating Task object with title "title"
// Task::GetTitle() should return "title"
TEST_F(TaskTest, GetTitle_shouldReturnTaskTitle){
    // Arrange
    std::string expected = "title";
    Task task = Task::Create(expected, Task::Priority::NONE, time(0));
    // Act
    std::string actual = task.GetTitle();
    // Assert
    EXPECT_EQ(expected, actual);
}

// Creating Task object with High Priority
// GetPriority should return Priority::HIGH
TEST_F(TaskTest, GetPriority_shouldReturnTaskPriority){
    // Arrange
    Task::Priority expected = Task::Priority::HIGH;
    Task task = Task::Create("title", expected, time(0));
    // Act
    Task::Priority actual = task.GetPriority();
    // Assert
    EXPECT_EQ(expected, actual);
}

TEST_F(TaskTest, GetDueTime_shouldReturnDueTime){
    // Arrange
    time_t expected = 1636739250;
    Task task = Task::Create("title", Task::Priority::NONE, 1636739250);
    // Act
    time_t actual = task.GetDueTime();
    // Assert
    EXPECT_EQ(expected, actual);
}

// Using Task::Create giving empty title
// Throws std::invalid_argument
TEST_F(TaskTest, creatingTaskWithEmpyTitle_shouldThrowInvalidArgument){
    EXPECT_THROW(Task::Create("", Task::Priority::NONE, time(0)), std::invalid_argument);
}

// Creating Task with Title = "title"
// Different priorities and due_date = 1636739250
// Should return correct string
TEST_F(TaskTest, usingToStringTaskMethod_shouldReturnCorrectString){
    // Arrange
    const int priorities_count = 4;
    time_t some_time = 1636739250;
    std::vector<Task> tasks;
    tasks.push_back(Task::Create("title", Task::Priority::HIGH, some_time));
    tasks.push_back(Task::Create("title", Task::Priority::MEDIUM, some_time));
    tasks.push_back(Task::Create("title", Task::Priority::LOW, some_time));
    tasks.push_back(Task::Create("title", Task::Priority::NONE, some_time));
    std::string priorities[priorities_count] { "High", "Medium", "Low", "None" };
    // Act & Assert
    for (int i = 0; i < priorities_count; ++i) {
        std::string expected = tasks[i].GetTitle() + ", Priority: " +
                priorities[i] + ", Due to: 1636739250\n";
        std::string actual = tasks[i].to_string();
        EXPECT_EQ(expected, actual);
    }
}