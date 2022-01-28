//
// Created by Maksym Kharchenko on 14.01.2022.
//

#include "gtest/gtest.h"

#include "utilities/TaskBuilder.h"
#include "utilities/TaskComparators.h"

#include <google/protobuf/util/time_util.h>

class TaskComparatorsTest : public ::testing::Test {
public:
    TaskId task_id1;
    TaskId task_id2;
    TaskId task_id3;

    Task task1;
    Task task2;
    Task task3;
    void SetUp() override {
        task_id1.set_id(10);
        task_id2.set_id(10);
        task_id3.set_id(42);

        task1 = TaskBuilder::Create()
                .SetTitle("task title")
                .SetPriority(Task::Priority::Task_Priority_HIGH)
                .SetDueDate(google::protobuf::util::TimeUtil::TimeTToTimestamp(1000))
                .AddLabel("task label")
                .BuildTask();
        task2 = TaskBuilder::Create()
                .SetTitle("task title")
                .SetPriority(Task::Priority::Task_Priority_HIGH)
                .SetDueDate(google::protobuf::util::TimeUtil::TimeTToTimestamp(1000))
                .AddLabel("task label")
                .BuildTask();
        task3 = TaskBuilder::Create()
                .SetTitle("task title")
                .SetPriority(Task::Priority::Task_Priority_LOW)
                .SetDueDate(google::protobuf::util::TimeUtil::TimeTToTimestamp(2000))
                .BuildTask();
    }
};

TEST_F(TaskComparatorsTest, TaskIdOperatorEqual_ShouldCheckTaskIdForEquality) {
    EXPECT_TRUE(task_id1 == task_id1);
    EXPECT_TRUE(task_id1 == task_id1);
    EXPECT_TRUE(task_id1 == task_id2);
    EXPECT_FALSE(task_id1 == task_id3);
    EXPECT_FALSE(task_id2 == task_id3);
}

TEST_F(TaskComparatorsTest, TaskIdOperatorLessThan) {
    EXPECT_FALSE(task_id1 < task_id1);
    EXPECT_FALSE(task_id3 < task_id3);
    EXPECT_TRUE(task_id1 < task_id3);
    EXPECT_FALSE(task_id3 < task_id1);
    EXPECT_FALSE(task_id1 < task_id2);
}

TEST_F(TaskComparatorsTest, TaskOperatorEquals_ShouldCheckTasksForEquality) {
    EXPECT_TRUE(task1 == task2);
    EXPECT_TRUE(task2 == task2);
    EXPECT_TRUE(task3 == task3);
    EXPECT_TRUE(task1 == task2);
    EXPECT_TRUE(task2 == task1);
    EXPECT_FALSE(task1 == task3);
    EXPECT_FALSE(task2 == task3);
    EXPECT_FALSE(task3 == task1);
    EXPECT_FALSE(task3 == task2);
}
