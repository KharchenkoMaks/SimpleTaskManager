//
// Created by Maksym Kharchenko on 10.12.2021.
//

#include "gtest/gtest.h"

#include "tasks/TaskBuilder.h"

class TaskBuilderTest : public ::testing::Test {

};

TEST_F(TaskBuilderTest, BuildTask_ShouldBuildRightTask) {
    // Arrange
    TaskBuilder task_builder;
    const std::string expected_title = "some title";
    const Task::Priority expected_priority = Task::Priority::LOW;
    const DueTime expected_due_time = DueTime::Create(1000);
    const bool expected_completion = true;
    const std::string expected_label = "some label!";
    const Task expected_built_task = Task::Create(expected_title, expected_priority, expected_due_time, expected_completion, expected_label);
    // Act
    task_builder
        .SetTitle(expected_title)
        .SetPriority(expected_priority)
        .SetDueTime(expected_due_time)
        .SetCompletionState(expected_completion)
        .SetLabel(expected_label);
    const std::optional<Task> actual_built_task = task_builder.BuildTask();
    // Assert
    ASSERT_NE(actual_built_task, std::nullopt);
    EXPECT_EQ(expected_built_task, actual_built_task.value());
}

TEST_F(TaskBuilderTest, AssignTaskBuilerTask_ShouldCreateRightTask) {
    // Arrange
    TaskBuilder task_builder;
    const std::string expected_title = "some title";
    const Task::Priority expected_priority = Task::Priority::LOW;
    const DueTime expected_due_time = DueTime::Create(1000);
    const bool expected_completion = true;
    const std::string expected_label = "some label!";
    const Task expected_built_task = Task::Create(expected_title, expected_priority, expected_due_time, expected_completion, expected_label);
    // Act
    task_builder = expected_built_task;
    const std::optional<Task> actual_built_task = task_builder.BuildTask();
    // Assert
    ASSERT_NE(actual_built_task, std::nullopt);
    EXPECT_EQ(expected_built_task, actual_built_task.value());
}

TEST_F(TaskBuilderTest, TryToBuildTaskWithEmptyBuilder_ShouldReturnNullopt) {
    // Arrange
    TaskBuilder task_builder;
    // Act
    std::optional<Task> built_task = task_builder.BuildTask();
    // Assert
    EXPECT_EQ(built_task, std::nullopt);
}