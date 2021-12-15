//
// Created by Maksym Kharchenko on 14.11.2021.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "TaskManager.h"
#include "id/IdGenerator.h"
#include "Task.pb.h"
#include "utilities/TaskActionResult.h"
#include "utilities/TaskUtilities.h"

#include <ctime>
#include <string>
#include <vector>
#include <utility>
#include <optional>
#include <google/protobuf/util/time_util.h>

using ::testing::Return;

class MockIdGenerator : public IdGenerator{
public:
    MOCK_METHOD(TaskId, CreateNewTaskId, (), (override));
};

class TaskManagerTest : public ::testing::Test {
public:
    google::protobuf::Timestamp expected_time;
    std::string expected_title[3] = { "task1", "task2", "task3" };
    Task::Priority expected_priority[3] =
            { Task::Priority::Task_Priority_NONE,
              Task::Priority::Task_Priority_LOW,
              Task::Priority::Task_Priority_MEDIUM};
    TaskId expected_first_task_id;
    TaskId expected_second_task_id;
    TaskId expected_third_task_id;
    Task expected_first_task;
    Task expected_second_task;
    Task expected_third_task;
    void SetUp() override {
        expected_time = google::protobuf::util::TimeUtil::TimeTToTimestamp(time(0));

        expected_first_task_id.set_id(1);
        expected_second_task_id.set_id(2);
        expected_third_task_id.set_id(5);

        expected_first_task.set_title(expected_title[0]);
        expected_first_task.set_priority(expected_priority[0]);
        expected_first_task.set_allocated_due_date(new google::protobuf::Timestamp(expected_time));
        expected_second_task.set_title(expected_title[1]);
        expected_second_task.set_priority(expected_priority[1]);
        expected_second_task.set_allocated_due_date(new google::protobuf::Timestamp(expected_time));
        expected_third_task.set_title(expected_title[2]);
        expected_third_task.set_priority(expected_priority[2]);
        expected_third_task.set_allocated_due_date(new google::protobuf::Timestamp(expected_time));
    }
};

// Creating two Tasks in TaskManager
// Should return right Tasks in GetTasks() method
TEST_F(TaskManagerTest, CreatingTasks_ShouldReturnTaskVector){
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);

    EXPECT_CALL(*gen, CreateNewTaskId())
        .Times(2)
        .WillOnce(Return(expected_first_task_id))
        .WillOnce(Return(expected_second_task_id));

    TaskManager task_manager(std::move(gen));
    // Act
    TaskId task1 = task_manager.AddTask(expected_first_task).second.value();
    TaskId task2 = task_manager.AddTask(expected_second_task).second.value();

    std::vector<TaskTransfer> tasks = task_manager.GetTasks();
    // Assert
    // Check size of task vector equals 2
    EXPECT_EQ(tasks.size(), 2);
    // Check equality of task1
    EXPECT_EQ(tasks[0].task_id(), expected_first_task_id);
    EXPECT_EQ(tasks[0].task().title(), expected_title[0]);
    EXPECT_EQ(tasks[0].task().priority(), expected_priority[0]);
    EXPECT_EQ(tasks[0].task().due_date(), expected_time);
    EXPECT_FALSE(tasks[0].has_parent_id());
    // Check equality of task2
    EXPECT_EQ(tasks[1].task_id(), expected_second_task_id);
    EXPECT_EQ(tasks[1].task().title(), expected_title[1]);
    EXPECT_EQ(tasks[1].task().priority(), expected_priority[1]);
    EXPECT_EQ(tasks[1].task().due_date(), expected_time);
    EXPECT_FALSE(tasks[1].has_parent_id());
}

// Editing existing Task in TaskManager
// Should return edited task
TEST_F(TaskManagerTest, EditingTask_ShouldReturnEditedTask){
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
        .Times(2)
        .WillOnce(Return(expected_first_task_id))
        .WillOnce(Return(expected_second_task_id));

    TaskManager task_manager(std::move(gen));
    const std::string expected_title = "edited task";
    const Task::Priority expected_priority = Task::Priority::Task_Priority_HIGH;
    const google::protobuf::Timestamp expected_time = google::protobuf::util::TimeUtil::TimeTToTimestamp(time(0));
    Task edited_task;
    edited_task.set_title(expected_title);
    edited_task.set_priority(expected_priority);
    edited_task.set_allocated_due_date(new google::protobuf::Timestamp(expected_time));

    TaskId main_task_id = task_manager.AddTask(expected_first_task).second.value();
    TaskId subtask_id = task_manager.AddSubTask(expected_second_task, main_task_id).second.value();
    // Act
    task_manager.EditTask(main_task_id, edited_task);
    task_manager.EditTask(subtask_id, edited_task);
    std::optional<TaskTransfer> actual_main = task_manager.GetTask(main_task_id);
    std::optional<TaskTransfer> actual_sub = task_manager.GetTask(subtask_id);
    // Assert
    ASSERT_NE(actual_main, std::nullopt);
    ASSERT_NE(actual_sub, std::nullopt);

    EXPECT_EQ(expected_first_task_id, actual_main.value().task_id());
    EXPECT_EQ(expected_title, actual_main.value().task().title());
    EXPECT_EQ(expected_priority, actual_main.value().task().priority());
    EXPECT_EQ(expected_time, actual_main.value().task().due_date());
    EXPECT_FALSE(actual_main.value().has_parent_id());

    EXPECT_EQ(expected_second_task_id, actual_sub.value().task_id());
    EXPECT_EQ(expected_title, actual_sub.value().task().title());
    EXPECT_EQ(expected_priority, actual_sub.value().task().priority());
    EXPECT_EQ(expected_time, actual_sub.value().task().due_date());
    EXPECT_EQ(actual_sub.value().parent_id(), main_task_id);
}

// Creating two Tasks in TaskManager
// Deleting first task
// GetTasks method should return only second task
TEST_F(TaskManagerTest, DeleteTask_ShouldDeleteTaskProperly){
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
        .Times(2)
        .WillOnce(Return(expected_first_task_id))
        .WillOnce(Return(expected_second_task_id));

    TaskManager task_manager(std::move(gen));
    TaskId task_id_1 = task_manager.AddTask(expected_first_task).second.value();
    TaskId task_id_2 = task_manager.AddTask(expected_second_task).second.value();
    // Act
    task_manager.DeleteTask(task_id_1);
    std::vector<TaskTransfer> tasks = task_manager.GetTasks();
    TaskId actual_task_id = tasks[0].task_id();
    Task actual_task = tasks[0].task();
    // Assert
    EXPECT_TRUE(tasks.size() == 1);
    EXPECT_TRUE(actual_task_id == expected_second_task_id);
    EXPECT_EQ(actual_task.title(), expected_title[1]);
    EXPECT_EQ(actual_task.priority(), expected_priority[1]);
    EXPECT_EQ(actual_task.due_date(), expected_time);
}

// Giving unused TaskId to EditTask() method
// Should return false
TEST_F(TaskManagerTest, TryEditingNonExistentTask_ShouldReturnFalse){
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
        .Times(0);

    TaskManager task_manager(std::move(gen));
    // Act & Assert
    EXPECT_EQ(task_manager.EditTask(expected_first_task_id, expected_first_task), TaskActionResult::FAIL_NO_SUCH_TASK);
}

// Giving unused TaskId to DeleteTask method
// Should return false
TEST_F(TaskManagerTest, TryDeletingNonExistentTask_ShouldReturnFalse){
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
        .Times(0);

    TaskManager task_manager(std::move(gen));
    // Act & Assert
    EXPECT_EQ(task_manager.DeleteTask(expected_first_task_id), TaskActionResult::FAIL_NO_SUCH_TASK);
}

// Creating three Tasks
// Completing first and third task
// First and third Tasks should be completed
TEST_F(TaskManagerTest, TryCompletingDifferentTasks_ShouldCompleteThoseTasks){
    // Arrange

    TaskManager task_manager(std::make_unique<IdGenerator>());

    const std::string expected_not_completed_title = "i am not completed";
    Task expected_not_completed_task;
    expected_not_completed_task.set_title(expected_not_completed_title);
    expected_not_completed_task.set_priority(Task::Priority::Task_Priority_HIGH);
    expected_not_completed_task.set_allocated_due_date(new google::protobuf::Timestamp(expected_time));

    TaskId task1 = task_manager.AddTask(expected_first_task).second.value();
    TaskId task2 = task_manager.AddTask(expected_not_completed_task).second.value();
    TaskId task3 = task_manager.AddTask(expected_second_task).second.value();
    // Act
    task_manager.CompleteTask(task1);
    task_manager.CompleteTask(task3);
    std::vector<TaskTransfer> tasks = task_manager.GetTasks();
    Task actual_first_completed_task = tasks[0].task();
    Task actual_second_completed_task = tasks[2].task();
    Task actual_not_completed_task = tasks[1].task();
    // Assert
    ASSERT_EQ(tasks.size(), 3);

    EXPECT_EQ(actual_first_completed_task.title(), expected_title[0]);
    EXPECT_TRUE(actual_first_completed_task.completed());
    EXPECT_EQ(actual_second_completed_task.title(), expected_title[1]);
    EXPECT_TRUE(actual_second_completed_task.completed());
    EXPECT_EQ(actual_not_completed_task.title(), expected_not_completed_title);
    EXPECT_FALSE(actual_not_completed_task.completed());
}

// Trying to complete non-existent TaskId
// Should return false
TEST_F(TaskManagerTest, TryCompletingNonExistentTask_ShouldReturnFalse){
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
            .Times(0);

    TaskManager task_manager(std::move(gen));
    // Act & Assert
    EXPECT_EQ(task_manager.CompleteTask(expected_first_task_id), TaskActionResult::FAIL_NO_SUCH_TASK);
}

// Adding subtask to task manager
// GetTask should return right subtask
TEST_F(TaskManagerTest, TryAddingSubtask_ShouldReturnRightTask) {
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
            .Times(2)
            .WillOnce(Return(expected_first_task_id))
            .WillOnce(Return(expected_second_task_id));

    TaskManager task_manager(std::move(gen));

    // Act
    TaskId main_task_id = task_manager.AddTask(expected_first_task).second.value();
    TaskId subtask_id = task_manager.AddSubTask(expected_second_task, main_task_id).second.value();
    std::optional<TaskTransfer> get_subtask = task_manager.GetTask(subtask_id);
    // Assert
    ASSERT_NE(get_subtask, std::nullopt);
    EXPECT_EQ(get_subtask.value().task_id(), subtask_id);
    EXPECT_EQ(get_subtask.value().parent_id(), main_task_id);
    EXPECT_EQ(get_subtask.value().task(), expected_second_task);
    EXPECT_TRUE(task_manager.IsTaskExist(subtask_id));
    EXPECT_TRUE(task_manager.IsTaskExist(main_task_id));
}

TEST_F(TaskManagerTest, TryGetNonExistentTask_ShouldReturnNullopt) {
    // Arrange
    TaskManager task_manager(std::make_unique<IdGenerator>());
    // Act
    std::optional<TaskTransfer> task = task_manager.GetTask(expected_first_task_id);
    // Assert
    EXPECT_EQ(task, std::nullopt);
}

TEST_F(TaskManagerTest, TryDeletingSubTask_ShouldDeleteSubTaskProperly) {
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
            .Times(3)
            .WillOnce(Return(expected_first_task_id))
            .WillOnce(Return(expected_second_task_id))
            .WillOnce(Return(expected_third_task_id));

    TaskManager task_manager(std::move(gen));

    TaskId main_task_id = task_manager.AddTask(expected_first_task).second.value();
    TaskId subtask1_id = task_manager.AddSubTask(expected_second_task, main_task_id).second.value();
    TaskId subtask2_id = task_manager.AddSubTask(expected_third_task, main_task_id).second.value();

    // Act
    task_manager.DeleteTask(subtask1_id);
    const std::vector<TaskTransfer> tasks = task_manager.GetTasks();
    const TaskTransfer main_task_transfer = tasks[0];
    const TaskTransfer subtask_transfer = tasks[1];

    // Assert
    ASSERT_EQ(tasks.size(), 2);

    EXPECT_EQ(main_task_transfer.task(), expected_first_task);
    EXPECT_EQ(main_task_transfer.task_id(), main_task_id);
    EXPECT_FALSE(main_task_transfer.has_parent_id());

    EXPECT_EQ(subtask_transfer.task(), expected_third_task);
    EXPECT_EQ(subtask_transfer.task_id(), subtask2_id);
    EXPECT_EQ(subtask_transfer.parent_id(), main_task_id);
}

TEST_F(TaskManagerTest, TryCompleteSubTask_ShouldCompleteSubTask) {
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
            .Times(3)
            .WillOnce(Return(expected_first_task_id))
            .WillOnce(Return(expected_second_task_id))
            .WillOnce(Return(expected_third_task_id));

    TaskManager task_manager(std::move(gen));

    TaskId main_task_id = task_manager.AddTask(expected_first_task).second.value();
    TaskId subtask1_id = task_manager.AddSubTask(expected_second_task, main_task_id).second.value();
    TaskId subtask2_id = task_manager.AddSubTask(expected_third_task, main_task_id).second.value();

    // Act
    task_manager.CompleteTask(subtask1_id);
    const std::optional<TaskTransfer> actual_subtask = task_manager.GetTask(subtask1_id);
    // Assert
    EXPECT_NE(actual_subtask, std::nullopt);
    EXPECT_TRUE(actual_subtask->task().completed());
}