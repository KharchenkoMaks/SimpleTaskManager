//
// Created by Maksym Kharchenko on 14.11.2021.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "TaskManager.h"
#include "IdGenerator.h"
#include "TaskId.h"
#include "DueTime.h"

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
// Should return right Tasks in Show() method
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
    TaskId task1 = task_manager.Add(Task::Create(expected_title[0],
                                                 expected_priority[0], expected_time));
    TaskId task2 = task_manager.Add(Task::Create(expected_title[1],
                                                 expected_priority[1], expected_time));

    std::vector<std::pair<TaskId, Task>> tasks = task_manager.Show();
    // Assert
    // Check size of task vector equals 2
    EXPECT_EQ(tasks.size(), 2);
    // Check equality of task1
    EXPECT_TRUE(tasks[0].first == task1);
    EXPECT_EQ(tasks[0].second.GetTitle(), expected_title[0]);
    EXPECT_EQ(tasks[0].second.GetPriority(), expected_priority[0]);
    EXPECT_EQ(tasks[0].second.GetDueTime(), expected_time);
    // Check equality of task2
    EXPECT_TRUE(tasks[1].first == task2);
    EXPECT_EQ(tasks[1].second.GetTitle(), expected_title[1]);
    EXPECT_EQ(tasks[1].second.GetPriority(), expected_priority[1]);
    EXPECT_EQ(tasks[1].second.GetDueTime(), expected_time);
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

    TaskId task1 = task_manager.Add(Task::Create("title",
                                                 Task::Priority::MEDIUM,
                                                 DueTime::Create(time(0))));
    // Act
    task_manager.Edit(task1,
                      Task::Create(expected_title, expected_priority, expected_time));
    std::pair<TaskId, Task> actual = task_manager.Show()[0];
    // Assert
    EXPECT_TRUE(task1 == actual.first);
    EXPECT_EQ(expected_title, actual.second.GetTitle());
    EXPECT_EQ(expected_priority, actual.second.GetPriority());
    EXPECT_EQ(expected_time, actual.second.GetDueTime());
}

// Creating two Tasks in TaskManager
// Deleting first task
// Show method should return only second task
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
    TaskId task_id_1 = task_manager.Add(task1);
    TaskId task_id_2 = task_manager.Add(task2);
    // Act
    task_manager.Delete(task_id_1);
    std::vector<std::pair<TaskId, Task>> tasks = task_manager.Show();
    TaskId actual_task_id = tasks[0].first;
    Task actual_task = tasks[0].second;
    // Assert
    EXPECT_TRUE(tasks.size() == 1);
    EXPECT_TRUE(actual_task_id == task_id_2);
    EXPECT_EQ(actual_task.GetTitle(), expected_title);
    EXPECT_EQ(actual_task.GetPriority(), expected_priority);
    EXPECT_EQ(actual_task.GetDueTime(), expected_time);
}

// Giving unused TaskId to Edit() method
// Should throw std::invalid_argument
TEST_F(TaskManagerTest, TryEditingNonExistentTask_ShouldThrowInvalidArgument){
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
        .Times(0);

    TaskManager task_manager(std::move(gen));
    TaskId task_id = TaskId::Create(5);
    Task task = Task::Create("title", Task::Priority::NONE, DueTime::Create(time(0)));
    // Act & Assert
    EXPECT_THROW(task_manager.Edit(task_id, task), std::invalid_argument);
}

// Giving unused TaskId to Delete method
// Should throw std::invalid argument
TEST_F(TaskManagerTest, TryDeletingNonExistentTask_ShouldThrowInvalidArgument){
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
        .Times(0);

    TaskManager task_manager(std::move(gen));
    TaskId task_id = TaskId::Create(5);
    // Act & Assert
    EXPECT_THROW(task_manager.Delete(task_id), std::invalid_argument);
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

    TaskId task1 = task_manager.Add(
            Task::Create("task1", Task::Priority::NONE, DueTime::Create(time(0))));
    TaskId task2 = task_manager.Add(
            Task::Create("task2", Task::Priority::NONE, DueTime::Create(time(0))));
    TaskId task3 = task_manager.Add(
            Task::Create("task3", Task::Priority::NONE, DueTime::Create(time(0))));
    // Act
    task_manager.Complete(task1);
    task_manager.Complete(task3);
    std::vector<std::pair<TaskId, Task>> tasks = task_manager.Show();
    Task actual_first_completed_task = tasks[0].second;
    Task actual_second_completed_task = tasks[2].second;
    Task actual_not_completed_task = tasks[1].second;
    // Assert
    ASSERT_EQ(tasks.size(), 3);

    EXPECT_EQ(expected_first_completed_task, actual_first_completed_task);
    EXPECT_EQ(expected_second_completed_task, actual_second_completed_task);
    EXPECT_EQ(expected_not_completed_task, actual_not_completed_task);
}

// Trying to complete non-existent TaskId
// Should throw std::invalid_argument
TEST_F(TaskManagerTest, TryCompletingNonExistentTask_ShouldThrowInvalidArgument){
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
            .Times(0);

    TaskManager task_manager(std::move(gen));
    // Act & Assert
    EXPECT_THROW(task_manager.Complete(TaskId::Create(5)), std::invalid_argument);
}