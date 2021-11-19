//
// Created by Maksym Kharchenko on 12.11.2021.
//

#include "gtest/gtest.h"
#include "Task.h"

#include <ctime>
#include <vector>

class TaskTest : public ::testing::Test {

};

TEST_F(TaskTest, NewTaskParametersShouldBeCorrect){
    // Arrange
    const std::string expected_title = "title";
    const Task::Priority expected_priority = Task::Priority::MEDIUM;
    const time_t expected_time = time(0);
    const bool expected_completion = true;
    const std::string expected_label = "some label";
    // Act
    Task task = Task::Create(expected_title,
                             expected_priority,
                             expected_time,
                             expected_completion,
                             expected_label);

    const std::string actual_title = task.GetTitle();
    const Task::Priority actual_priority = task.GetPriority();
    const time_t actual_time = task.GetDueTime();
    const bool actual_completion = task.IsCompleted();
    const std::string actual_label = task.GetLabel();
    // Assert
    EXPECT_EQ(expected_title, actual_title);
    EXPECT_EQ(expected_priority, actual_priority);
    EXPECT_EQ(expected_time, actual_time);
    EXPECT_EQ(expected_completion, actual_completion);
    EXPECT_EQ(expected_label, actual_label);
}

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

// Creating new task
// It should be uncompleted
TEST_F(TaskTest, newTaskShouldBeUncompleted){
    // Arrange
    Task task = Task::Create("title", Task::Priority::HIGH, time(0));
    // Assert
    EXPECT_FALSE(task.IsCompleted());
}

TEST_F(TaskTest, shouldReturnRightTaskLabel){
    // Arrange
    std::string expected1 = "";
    std::string expected2 = "some label";

    Task task_without_label =
            Task::Create("title", Task::Priority::HIGH, time(0));
    Task task_with_label =
            Task::Create("title", Task::Priority::HIGH, time(0), false, expected2);
    // Act
    std::string acutal1 = task_without_label.GetLabel();
    std::string actual2 = task_with_label.GetLabel();
    // Asset
    EXPECT_EQ(expected1, acutal1);
    EXPECT_EQ(expected2, actual2);
}

TEST_F(TaskTest, OperatorEqualsShouldReturnTrueForEqualTasks){
    // Arrange
    const time_t some_time = time(0);
    Task task1 = Task::Create("title", Task::Priority::NONE, some_time);
    Task task2 = Task::Create("title", Task::Priority::NONE, some_time);
    // Act & Assert
    EXPECT_TRUE(task1 == task2);
    EXPECT_TRUE(task2 == task1);
}

TEST_F(TaskTest, OperatorEqualsShouldReturnFalseForNotEqualTasks){
    // Arrange
    const time_t some_time = time(0);
    Task task1 = Task::Create("title", Task::Priority::NONE, some_time);
    Task task2 = Task::Create("title2", Task::Priority::NONE, some_time);
    Task task3 = Task::Create("title", Task::Priority::LOW, some_time);
    Task task4 = Task::Create("title", Task::Priority::NONE, some_time + 5);
    Task task5 = Task::Create("title", Task::Priority::NONE, some_time, true);
    Task task6 = Task::Create("title", Task::Priority::NONE, some_time, false, "some label");
    // Act & Assert
    EXPECT_FALSE(task1 == task2);
    EXPECT_FALSE(task1 == task3);
    EXPECT_FALSE(task1 == task4);
    EXPECT_FALSE(task1 == task5);
    EXPECT_FALSE(task1 == task6);
}