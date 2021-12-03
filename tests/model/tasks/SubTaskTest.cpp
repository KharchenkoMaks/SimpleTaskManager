//
// Created by Maksym Kharchenko on 03.12.2021.
//

#include "gtest/gtest.h"
#include "tasks/SubTask.h"
#include "DueTime.h"

class SubTaskTest : public ::testing::Test {

};

TEST_F(SubTaskTest, CreatingTwoEqualSubTasks_ShouldBeEquals) {
    // Arrange
    SubTask task1 = SubTask::Create("Task", Task::Priority::LOW, DueTime::Create(1000), TaskId::Create(5).value());
    SubTask task2 = SubTask::Create("Task", Task::Priority::LOW, DueTime::Create(1000), TaskId::Create(5).value());
    // Act & Assert
    EXPECT_EQ(task1, task2);
}

TEST_F(SubTaskTest, CreatingSubTask_GetParentIdShouldReturnRightId) {
    // Arrange
    const TaskId expected = TaskId::Create(5).value();
    SubTask task1 = SubTask::Create("Task", Task::Priority::LOW, DueTime::Create(1000), expected);
    // Act
    const TaskId actual = task1.GetParentTaskId();
    // Assert
    EXPECT_EQ(expected, actual);
}