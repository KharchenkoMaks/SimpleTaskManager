//
// Created by Maksym Kharchenko on 14.11.2021.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "TaskManager.h"
#include "id/IdGenerator.h"
#include "id/TaskId.h"
#include "DueTime.h"
#include "abstract_model/TaskTransfer.h"
#include "tasks/SubTask.h"
#include "utilities/TaskActionResult.h"

#include <ctime>
#include <string>
#include <vector>
#include <utility>
#include <optional>

using ::testing::Return;

class MockIdGenerator : public IdGenerator{
public:
    MOCK_METHOD(TaskId, CreateNewTaskId, (), (override));
};

class TaskManagerTest : public ::testing::Test{

};

// Creating two Tasks in TaskManager
// Should return right Tasks in GetTasks() method
TEST_F(TaskManagerTest, CreatingTasks_ShouldReturnTaskVector){
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
        .Times(2)
        .WillOnce(Return(TaskId::Create(1).value()))
        .WillOnce(Return(TaskId::Create(2).value()));

    TaskManager task_manager(std::move(gen));

    const DueTime expected_time = DueTime::Create(time(0));
    const std::string expected_title[] = { "task1", "task2" };
    const Task::Priority expected_priority[] =
            { Task::Priority::NONE,Task::Priority::LOW };
    // Act
    TaskId task1 = task_manager.AddTask(Task::Create(expected_title[0],
                                                     expected_priority[0], expected_time)).second.value();
    TaskId task2 = task_manager.AddTask(Task::Create(expected_title[1],
                                                     expected_priority[1], expected_time)).second.value();

    std::vector<TaskTransfer> tasks = task_manager.GetTasks();
    // Assert
    // Check size of task vector equals 2
    EXPECT_EQ(tasks.size(), 2);
    // Check equality of task1
    EXPECT_TRUE(tasks[0].GetTaskId() == task1);
    EXPECT_EQ(tasks[0].GetTask().GetTitle(), expected_title[0]);
    EXPECT_EQ(tasks[0].GetTask().GetPriority(), expected_priority[0]);
    EXPECT_EQ(tasks[0].GetTask().GetDueTime(), expected_time);
    // Check equality of task2
    EXPECT_TRUE(tasks[1].GetTaskId() == task2);
    EXPECT_EQ(tasks[1].GetTask().GetTitle(), expected_title[1]);
    EXPECT_EQ(tasks[1].GetTask().GetPriority(), expected_priority[1]);
    EXPECT_EQ(tasks[1].GetTask().GetDueTime(), expected_time);
}

// Editing existing Task in TaskManager
// Should return edited task
TEST_F(TaskManagerTest, EditingTask_ShouldReturnEditedTask){
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
        .Times(2)
        .WillOnce(Return(TaskId::Create(0).value()))
        .WillOnce(Return(TaskId::Create(1).value()));

    TaskManager task_manager(std::move(gen));
    const std::string expected_title = "edited task";
    const Task::Priority expected_priority = Task::Priority::HIGH;
    const DueTime expected_time = DueTime::Create(time(0));

    TaskId main_task_id = task_manager.AddTask(Task::Create("title",
                                                     Task::Priority::MEDIUM,
                                                     DueTime::Create(time(0)))).second.value();
    TaskId subtask_id = task_manager.AddSubTask(Task::Create("SubTask",
                                                             Task::Priority::LOW,
                                                             DueTime::Create(time(0))), main_task_id).second.value();
    // Act
    task_manager.EditTask(main_task_id,
                          Task::Create(expected_title, expected_priority, expected_time));
    task_manager.EditTask(subtask_id,
                          Task::Create(expected_title, expected_priority, expected_time));
    std::optional<TaskTransfer> actual_main = task_manager.GetTask(main_task_id);
    std::optional<TaskTransfer> actual_sub = task_manager.GetTask(subtask_id);
    // Assert
    ASSERT_NE(actual_main, std::nullopt);
    ASSERT_NE(actual_main, std::nullopt);

    EXPECT_EQ(main_task_id, actual_main.value().GetTaskId());
    EXPECT_EQ(expected_title, actual_main.value().GetTask().GetTitle());
    EXPECT_EQ(expected_priority, actual_main.value().GetTask().GetPriority());
    EXPECT_EQ(expected_time, actual_main.value().GetTask().GetDueTime());

    EXPECT_EQ(subtask_id, actual_sub.value().GetTaskId());
    EXPECT_EQ(expected_title, actual_sub.value().GetTask().GetTitle());
    EXPECT_EQ(expected_priority, actual_sub.value().GetTask().GetPriority());
    EXPECT_EQ(expected_time, actual_sub.value().GetTask().GetDueTime());
    EXPECT_EQ(actual_sub.value().GetParentTaskId(), main_task_id);
}

// Creating two Tasks in TaskManager
// Deleting first task
// GetTasks method should return only second task
TEST_F(TaskManagerTest, DeleteTask_ShouldDeleteTaskProperly){
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
        .Times(2)
        .WillOnce(Return(TaskId::Create(1).value()))
        .WillOnce(Return(TaskId::Create(10).value()));

    TaskManager task_manager(std::move(gen));
    const std::string expected_title = "second task";
    const Task::Priority expected_priority = Task::Priority::NONE;
    const DueTime expected_time = DueTime::Create(time(0));
    Task task1 = Task::Create("some title", Task::Priority::NONE, DueTime::Create(time(0)));
    Task task2 = Task::Create(expected_title, expected_priority, expected_time);
    TaskId task_id_1 = task_manager.AddTask(task1).second.value();
    TaskId task_id_2 = task_manager.AddTask(task2).second.value();
    // Act
    task_manager.DeleteTask(task_id_1);
    std::vector<TaskTransfer> tasks = task_manager.GetTasks();
    TaskId actual_task_id = tasks[0].GetTaskId();
    Task actual_task = tasks[0].GetTask();
    // Assert
    EXPECT_TRUE(tasks.size() == 1);
    EXPECT_TRUE(actual_task_id == task_id_2);
    EXPECT_EQ(actual_task.GetTitle(), expected_title);
    EXPECT_EQ(actual_task.GetPriority(), expected_priority);
    EXPECT_EQ(actual_task.GetDueTime(), expected_time);
}

// Giving unused TaskId to EditTask() method
// Should return false
TEST_F(TaskManagerTest, TryEditingNonExistentTask_ShouldReturnFalse){
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
        .Times(0);

    TaskManager task_manager(std::move(gen));
    TaskId task_id = TaskId::Create(5).value();
    Task task = Task::Create("title", Task::Priority::NONE, DueTime::Create(time(0)));
    // Act & Assert
    EXPECT_EQ(task_manager.EditTask(task_id, task), TaskActionResult::FAIL_NO_SUCH_TASK);
}

// Giving unused TaskId to DeleteTask method
// Should return false
TEST_F(TaskManagerTest, TryDeletingNonExistentTask_ShouldReturnFalse){
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
        .Times(0);

    TaskManager task_manager(std::move(gen));
    TaskId task_id = TaskId::Create(5).value();
    // Act & Assert
    EXPECT_EQ(task_manager.DeleteTask(task_id), TaskActionResult::FAIL_NO_SUCH_TASK);
}

// Creating three Tasks
// Completing first and third task
// First and third Tasks should be completed
TEST_F(TaskManagerTest, TryCompletingDifferentTasks_ShouldCompleteThoseTasks){
    // Arrange
    const DueTime some_time = DueTime::Create(time(0));

    TaskManager task_manager(std::make_unique<IdGenerator>());

    Task expected_first_completed_task =
            Task::Create("task1", Task::Priority::NONE, some_time, true);
    Task expected_not_completed_task =
            Task::Create("task2", Task::Priority::NONE, DueTime::Create(time(0)), false);
    Task expected_second_completed_task =
            Task::Create("task3", Task::Priority::NONE, some_time, true);

    TaskId task1 = task_manager.AddTask(
            Task::Create("task1", Task::Priority::NONE, DueTime::Create(time(0)))).second.value();
    TaskId task2 = task_manager.AddTask(
            Task::Create("task2", Task::Priority::NONE, DueTime::Create(time(0)))).second.value();
    TaskId task3 = task_manager.AddTask(
            Task::Create("task3", Task::Priority::NONE, DueTime::Create(time(0)))).second.value();
    // Act
    task_manager.CompleteTask(task1);
    task_manager.CompleteTask(task3);
    std::vector<TaskTransfer> tasks = task_manager.GetTasks();
    Task actual_first_completed_task = tasks[0].GetTask();
    Task actual_second_completed_task = tasks[2].GetTask();
    Task actual_not_completed_task = tasks[1].GetTask();
    // Assert
    ASSERT_EQ(tasks.size(), 3);

    EXPECT_EQ(expected_first_completed_task, actual_first_completed_task);
    EXPECT_EQ(expected_second_completed_task, actual_second_completed_task);
    EXPECT_EQ(expected_not_completed_task, actual_not_completed_task);
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
    EXPECT_EQ(task_manager.CompleteTask(TaskId::Create(5).value()), TaskActionResult::FAIL_NO_SUCH_TASK);
}

// Adding subtask to task manager
// GetTask should return right subtask
TEST_F(TaskManagerTest, TryAddingSubtask_ShouldReturnRightTask) {
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
            .Times(2)
            .WillOnce(Return(TaskId::Create(1).value()))
            .WillOnce(Return(TaskId::Create(10).value()));

    TaskManager task_manager(std::move(gen));

    Task main_task = Task::Create("Main Task", Task::Priority::NONE, DueTime::Create(time(0)));
    Task subtask = Task::Create("SubTask", Task::Priority::LOW, DueTime::Create(time(0)));
    // Act
    TaskId main_task_id = task_manager.AddTask(main_task).second.value();
    TaskId subtask_id = task_manager.AddSubTask(subtask, main_task_id).second.value();
    std::optional<TaskTransfer> get_subtask = task_manager.GetTask(subtask_id);
    // Assert
    ASSERT_NE(get_subtask, std::nullopt);
    EXPECT_EQ(get_subtask.value().GetTaskId(), subtask_id);
    EXPECT_EQ(get_subtask.value().GetParentTaskId(), main_task_id);
    EXPECT_EQ(get_subtask.value().GetTask(), subtask);
    EXPECT_TRUE(task_manager.IsTaskExist(subtask_id));
    EXPECT_TRUE(task_manager.IsTaskExist(main_task_id));
}

TEST_F(TaskManagerTest, TryGetNonExistentTask_ShouldReturnNullopt) {
    // Arrange
    TaskManager task_manager(std::make_unique<IdGenerator>());
    // Act
    std::optional<TaskTransfer> task = task_manager.GetTask(TaskId::Create(10).value());
    // Assert
    EXPECT_EQ(task, std::nullopt);
}

TEST_F(TaskManagerTest, TryDeletingSubTask_ShouldDeleteSubTaskProperly) {
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
            .Times(3)
            .WillOnce(Return(TaskId::Create(1).value()))
            .WillOnce(Return(TaskId::Create(10).value()))
            .WillOnce(Return(TaskId::Create(15).value()));

    TaskManager task_manager(std::move(gen));

    const std::string expected_main_title = "Main Task";
    const Task::Priority expected_main_priority = Task::Priority::HIGH;
    const DueTime expected_main_due_time = DueTime::Create(1000);

    const std::string expected_sub_title = "SubTask2";
    const Task::Priority expected_sub_priority = Task::Priority::NONE;
    const DueTime expected_sub_due_time = DueTime::Create(3000);

    Task main_task = Task::Create(expected_main_title, expected_main_priority, expected_main_due_time);
    Task subtask1 = Task::Create("SubTask1", Task::Priority::HIGH, DueTime::Create(time(0)));
    Task subtask2 = Task::Create(expected_sub_title, expected_sub_priority, expected_sub_due_time);

    TaskId main_task_id = task_manager.AddTask(main_task).second.value();
    TaskId subtask1_id = task_manager.AddSubTask(subtask1, main_task_id).second.value();
    TaskId subtask2_id = task_manager.AddSubTask(subtask2, main_task_id).second.value();

    // Act
    task_manager.DeleteTask(subtask1_id);
    const std::vector<TaskTransfer> tasks = task_manager.GetTasks();
    const TaskTransfer main_task_transfer = tasks[0];
    const TaskTransfer subtask_transfer = tasks[1];

    // Assert
    ASSERT_EQ(tasks.size(), 2);

    EXPECT_EQ(main_task_transfer.GetTask(), main_task);
    EXPECT_EQ(main_task_transfer.GetTaskId(), main_task_id);
    EXPECT_EQ(main_task_transfer.GetParentTaskId(), std::nullopt);

    EXPECT_EQ(subtask_transfer.GetTask(), subtask2);
    EXPECT_EQ(subtask_transfer.GetTaskId(), subtask2_id);
    EXPECT_EQ(subtask_transfer.GetParentTaskId(), main_task_id);
}

TEST_F(TaskManagerTest, TryCompleteSubTask_ShouldCompleteSubTask) {
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
            .Times(3)
            .WillOnce(Return(TaskId::Create(1).value()))
            .WillOnce(Return(TaskId::Create(10).value()))
            .WillOnce(Return(TaskId::Create(15).value()));

    TaskManager task_manager(std::move(gen));

    Task main_task = Task::Create("Main task", Task::Priority::NONE, DueTime::Create(time(0)));
    Task subtask1 = Task::Create("SubTask1", Task::Priority::HIGH, DueTime::Create(time(0)));
    Task subtask2 = Task::Create("SubTask2", Task::Priority::LOW, DueTime::Create(time(0)));

    TaskId main_task_id = task_manager.AddTask(main_task).second.value();
    TaskId subtask1_id = task_manager.AddSubTask(subtask1, main_task_id).second.value();
    TaskId subtask2_id = task_manager.AddSubTask(subtask2, main_task_id).second.value();

    // Act
    task_manager.CompleteTask(subtask1_id);
    const std::optional<TaskTransfer> actual_subtask = task_manager.GetTask(subtask1_id);
    // Assert
    EXPECT_NE(actual_subtask, std::nullopt);
    EXPECT_TRUE(actual_subtask->GetTask().IsCompleted());
}