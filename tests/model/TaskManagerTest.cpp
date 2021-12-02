//
// Created by Maksym Kharchenko on 14.11.2021.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "TaskManager.h"
#include "IdGenerator.h"
#include "TaskId.h"
#include "DueTime.h"
#include "abstract_model/TaskTransfer.h"

#include <ctime>
#include <string>
#include <vector>
#include <utility>

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
        .WillOnce(Return(TaskId::Create(1)))
        .WillOnce(Return(TaskId::Create(2)));

    TaskManager task_manager(std::move(gen));

    const DueTime expected_time = DueTime::Create(time(0));
    const std::string expected_title[] = { "task1", "task2" };
    const Task::Priority expected_priority[] =
            { Task::Priority::NONE,Task::Priority::LOW };
    // Act
    TaskId task1 = task_manager.AddTask(Task::Create(expected_title[0],
                                                     expected_priority[0], expected_time)).value();
    TaskId task2 = task_manager.AddTask(Task::Create(expected_title[1],
                                                     expected_priority[1], expected_time)).value();

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
        .Times(1)
        .WillOnce(Return(TaskId::Create(0)));

    TaskManager task_manager(std::move(gen));
    const std::string expected_title = "edited task";
    const Task::Priority expected_priority = Task::Priority::HIGH;
    const DueTime expected_time = DueTime::Create(time(0));

    TaskId task1 = task_manager.AddTask(Task::Create("title",
                                                     Task::Priority::MEDIUM,
                                                     DueTime::Create(time(0)))).value();
    // Act
    task_manager.EditTask(task1,
                          Task::Create(expected_title, expected_priority, expected_time));
    TaskTransfer actual = task_manager.GetTasks()[0];
    // Assert
    EXPECT_TRUE(task1 == actual.GetTaskId());
    EXPECT_EQ(expected_title, actual.GetTask().GetTitle());
    EXPECT_EQ(expected_priority, actual.GetTask().GetPriority());
    EXPECT_EQ(expected_time, actual.GetTask().GetDueTime());
}

// Creating two Tasks in TaskManager
// Deleting first task
// GetTasks method should return only second task
TEST_F(TaskManagerTest, DeleteTask_ShouldDeleteTaskProperly){
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
        .Times(2)
        .WillOnce(Return(TaskId::Create(1)))
        .WillOnce(Return(TaskId::Create(10)));

    TaskManager task_manager(std::move(gen));
    const std::string expected_title = "second task";
    const Task::Priority expected_priority = Task::Priority::NONE;
    const DueTime expected_time = DueTime::Create(time(0));
    Task task1 = Task::Create("some title", Task::Priority::NONE, DueTime::Create(time(0)));
    Task task2 = Task::Create(expected_title, expected_priority, expected_time);
    TaskId task_id_1 = task_manager.AddTask(task1).value();
    TaskId task_id_2 = task_manager.AddTask(task2).value();
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
    TaskId task_id = TaskId::Create(5);
    Task task = Task::Create("title", Task::Priority::NONE, DueTime::Create(time(0)));
    // Act & Assert
    EXPECT_FALSE(task_manager.EditTask(task_id, task));
}

// Giving unused TaskId to DeleteTask method
// Should return false
TEST_F(TaskManagerTest, TryDeletingNonExistentTask_ShouldReturnFalse){
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
        .Times(0);

    TaskManager task_manager(std::move(gen));
    TaskId task_id = TaskId::Create(5);
    // Act & Assert
    EXPECT_FALSE(task_manager.DeleteTask(task_id));
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
            Task::Create("task1", Task::Priority::NONE, DueTime::Create(time(0)))).value();
    TaskId task2 = task_manager.AddTask(
            Task::Create("task2", Task::Priority::NONE, DueTime::Create(time(0)))).value();
    TaskId task3 = task_manager.AddTask(
            Task::Create("task3", Task::Priority::NONE, DueTime::Create(time(0)))).value();
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
    EXPECT_FALSE(task_manager.CompleteTask(TaskId::Create(5)));
}