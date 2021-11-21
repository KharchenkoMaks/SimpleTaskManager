//
// Created by Maksym Kharchenko on 21.11.2021.
//

#include "gtest/gtest.h"
#include "Tasks/SubTask.h"

#include <ctime>

class SubTaskTest : public ::testing::Test {

};

TEST_F(SubTaskTest, CreatingTwoEqualSubTasks_AllParametersShouldBeRight){
    // Arrange
    std::string expected_title = "title";
    Task::Priority expected_priority = Task::Priority::MEDIUM;
    time_t expected_due_time = time(0);
    TaskId expected_parent = TaskId::Create(5);
    bool expected_completion = true;
    std::string expected_label = "some label";
    // Act
    SubTask task1 = SubTask::Create(expected_title,
                                    expected_priority,
                                    expected_due_time,
                                    expected_parent,
                                    expected_completion,
                                    expected_label);
    SubTask task2 = SubTask::Create(expected_title,
                                    expected_priority,
                                    expected_due_time,
                                    expected_parent,
                                    expected_completion,
                                    expected_label);
    // Assert
    EXPECT_EQ(task1, task2);

    EXPECT_EQ(task1.GetTitle(), expected_title);
    EXPECT_EQ(task1.GetPriority(), expected_priority);
    EXPECT_EQ(task1.GetDueTime(), expected_due_time);
    EXPECT_EQ(task1.GetParentTaskId(), expected_parent);
    EXPECT_EQ(task1.IsCompleted(), expected_completion);
    EXPECT_EQ(task1.GetLabel(), expected_label);

    EXPECT_EQ(task2.GetTitle(), expected_title);
    EXPECT_EQ(task2.GetPriority(), expected_priority);
    EXPECT_EQ(task2.GetDueTime(), expected_due_time);
    EXPECT_EQ(task2.GetParentTaskId(), expected_parent);
    EXPECT_EQ(task2.IsCompleted(), expected_completion);
    EXPECT_EQ(task2.GetLabel(), expected_label);
}