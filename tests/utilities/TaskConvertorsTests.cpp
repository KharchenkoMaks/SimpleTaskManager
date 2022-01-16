//
// Created by Maksym Kharchenko on 16.01.2022.
//

#include "gtest/gtest.h"

#include "utilities/TaskConvertors.h"
#include "utilities/TaskBuilder.h"

#include <vector>

class TaskConvertorsTest : public ::testing::Test {

};

TEST_F(TaskConvertorsTest, TaskPriorityToString_ShouldConvertTaskPriorityToString) {
    // Arrange
    const std::vector<Task::Priority> expected_task_priorities {
        Task::Priority::Task_Priority_NONE,
        Task::Priority::Task_Priority_LOW,
        Task::Priority::Task_Priority_MEDIUM,
        Task::Priority::Task_Priority_HIGH
    };
    const std::vector<std::string> expected_priorities_strings {
        "None",
        "Low",
        "Medium",
        "High"
    };
    // Act & Assert
    for (int i = 0; i < expected_task_priorities.size(); ++i) {
        const std::string actual_string = TaskPriorityToString(expected_task_priorities[i]);
        EXPECT_EQ(expected_priorities_strings[i], actual_string);
    }
}

TEST_F(TaskConvertorsTest, StringToTaskPriority_ShouldConvertStringToTaskPriority) {
    // Arrange
    const std::vector<std::optional<Task::Priority>> expected_task_priorities {
            Task::Priority::Task_Priority_NONE,
            Task::Priority::Task_Priority_LOW,
            Task::Priority::Task_Priority_MEDIUM,
            Task::Priority::Task_Priority_HIGH,
            std::nullopt
    };
    const std::vector<std::string> expected_priorities_strings {
            "None",
            "Low",
            "Medium",
            "High",
            "qwe"
    };
    // Act & Assert
    for (int i = 0; i < expected_task_priorities.size(); ++i) {
        const std::optional<Task::Priority> actual_task_priority =
                StringToTaskPriority(expected_priorities_strings[i]);
        EXPECT_EQ(expected_task_priorities[i], actual_task_priority);
    }
}

TEST_F(TaskConvertorsTest, StringToTime_ShouldConvertStringToTime) {
    // Arrange
    const google::protobuf::Timestamp expected_time = google::protobuf::util::TimeUtil::TimeTToTimestamp(1638286140);
    const std::string expected_string = "17:29 30.11.2021";
    // Act
    const auto actual_time = StringToTime(expected_string);
    // Assert
    ASSERT_TRUE(actual_time.has_value());
    EXPECT_EQ(expected_time, actual_time.value());
}

TEST_F(TaskConvertorsTest, StringToTime_ShouldReturnNulloptForIncorrectTime) {
    EXPECT_EQ(StringToTime("31"), std::nullopt);
    EXPECT_EQ(StringToTime("17:30"), std::nullopt);
    EXPECT_EQ(StringToTime("17:30 01.10"), std::nullopt);
    EXPECT_EQ(StringToTime("-17:30 01.10.2021"), std::nullopt);
    EXPECT_EQ(StringToTime("17:30 01.2021"), std::nullopt);
    EXPECT_EQ(StringToTime("17:30 01.10.-2021"), std::nullopt);
}

TEST_F(TaskConvertorsTest, TaskToString_ShouldConvertTaskToString) {
    // Arrange
    Task task1 = TaskBuilder::Create()
            .SetTitle("task")
            .SetPriority(Task::Priority::Task_Priority_LOW)
            .SetDueDate(StringToTime("17:29 30.11.2021").value())
            .BuildTask();
    Task task2 = TaskBuilder::Create()
            .SetTitle("task2")
            .SetPriority(Task::Priority::Task_Priority_HIGH)
            .SetDueDate(StringToTime("17:29 30.11.2021").value())
            .SetCompletion(true)
            .SetLabel("label for task2")
            .BuildTask();
    const std::vector<Task> expected_tasks { task1, task2 };
    const std::vector<std::string> expected_strings {
        "ID: 0, task, Priority: Low, Due to: 17:29 30.11.2021, Completed: No",
        "ID: 0, task2, Priority: High, Due to: 17:29 30.11.2021, Completed: Yes, Label: label for task2"
    };
    // Act & Assert
    for (int i = 0; i < expected_tasks.size(); ++i) {
        const std::string actual_string = TaskToString(TaskId::default_instance(), expected_tasks[i]);
        EXPECT_EQ(expected_strings[i], actual_string);
    }
}

TEST_F(TaskConvertorsTest, StringToTaskId_ShouldConvertStringsToTaskId) {
    // Arrange
    const int test_times = 100;
    // Act & Assert
    for (int i = 0; i < test_times; ++i) {
        const int expected_id = rand();
        const std::optional<TaskId> actual_task_id = StringToTaskId(std::to_string(expected_id));
        ASSERT_TRUE(actual_task_id.has_value());
        EXPECT_EQ(expected_id, actual_task_id.value().id());
    }
}

TEST_F(TaskConvertorsTest, StringToTaskId_ShouldReturnNulloptOnInvalidTaskId) {
    EXPECT_EQ(StringToTaskId(""), std::nullopt);
    EXPECT_EQ(StringToTaskId("qwe"), std::nullopt);
    EXPECT_EQ(StringToTaskId("-42"), std::nullopt);
    EXPECT_EQ(StringToTaskId("aaa"), std::nullopt);
}
