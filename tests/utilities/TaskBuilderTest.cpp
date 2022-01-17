//
// Created by Maksym Kharchenko on 13.01.2022.
//

#include "gtest/gtest.h"

#include "utilities/TaskBuilder.h"
#include "utilities/TaskComparators.h"

#include <google/protobuf/util/time_util.h>

class TaskBuilderTest : public ::testing::Test {
public:
    const std::string expected_title = "some title";
    const Task::Priority expected_priority = Task::Priority::Task_Priority_LOW;
    const google::protobuf::Timestamp expected_due_time = google::protobuf::util::TimeUtil::TimeTToTimestamp(1000);
    const bool expected_completion = true;
    const std::string expected_label = "some label!";
    const std::string expected_second_label = "second label";

    Task expected_built_task;
    void SetUp() override {
        expected_built_task.set_title(expected_title);
        expected_built_task.set_priority(expected_priority);
        expected_built_task.set_allocated_due_date(new google::protobuf::Timestamp(expected_due_time));
        expected_built_task.set_completed(expected_completion);
        expected_built_task.add_label(expected_second_label);
    }
};

TEST_F(TaskBuilderTest, BuildTask_ShouldBuildRightTask) {
    // Arrange
    TaskBuilder task_builder = TaskBuilder::Create();
    // Act
    task_builder
            .SetTitle(expected_title)
            .SetPriority(expected_priority)
            .SetDueDate(expected_due_time)
            .SetCompletion(expected_completion)
            .AddLabel(expected_label)
            .AddLabel(expected_second_label)
            .RemoveLabel(expected_label);
    const Task actual_built_task = task_builder.BuildTask();
    // Assert
    EXPECT_EQ(expected_built_task, actual_built_task);
}

TEST_F(TaskBuilderTest, TryToBuildTaskWithEmptyBuilder_ShouldReturnDefaultTask) {
    // Arrange
    TaskBuilder task_builder = TaskBuilder::Create();
    // Act
    Task built_task = task_builder.BuildTask();
    // Assert
    EXPECT_EQ(built_task, Task::default_instance());
}

TEST_F(TaskBuilderTest, Merge_ShouldMergeWithTask) {
    TaskBuilder task_builder = TaskBuilder::Create();
    // Act
    task_builder.Merge(expected_built_task);
    Task actual_built_task = task_builder.BuildTask();
    // Assert
    EXPECT_EQ(expected_built_task, actual_built_task);
}