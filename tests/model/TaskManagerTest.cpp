//
// Created by Maksym Kharchenko on 14.11.2021.
//

#include "gtest/gtest.h"
#include "../../src/model/TaskManager.h"
#include "../../src/model/TaskId.h"

#include <ctime>
#include <string>
#include <vector>
#include <utility>

class TaskManagerTest : public ::testing::Test{

};

// Creating two tasks in TaskManager
// Should return right tasks in Show() method
TEST_F(TaskManagerTest, CreatingTasks_ShouldReturnTaskVector){
    // Arrange
    TaskManager task_manager;
    const time_t expected_time = time(0);
    const std::string expected_title[] = { "task1", "task2" };
    const Task::Priority expected_priority[] =
            { Task::Priority::NONE,Task::Priority::LOW };
    // Act
    TaskId task1 = task_manager.Create(Task::Create(expected_title[0],
                                     expected_priority[0], expected_time));
    TaskId task2 = task_manager.Create(Task::Create(expected_title[1],
                                     expected_priority[1], expected_time));

    std::vector<std::pair<TaskId, Task>> tasks = task_manager.Show();
    // Assert
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
    TaskManager task_manager;
    const std::string expected_title = "edited task";
    const Task::Priority expected_priority = Task::Priority::HIGH;
    const time_t expected_time = time(0);

    TaskId task1 = task_manager.Create(Task::Create("title",
                                                    Task::Priority::MEDIUM,
                                                    time(0)));
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

// Creating two tasks in TaskManager
// Deleting first task
// Show method should return only second task
TEST_F(TaskManagerTest, DeleteTask_ShouldDeleteTaskProperly){
    // Arrange
    TaskManager task_manager;
    const std::string expected_title = "second task";
    const Task::Priority expected_priority = Task::Priority::NONE;
    const time_t expected_time = time(0);
    Task task1 = Task::Create("some title", Task::Priority::NONE, time(0));
    Task task2 = Task::Create(expected_title, expected_priority, expected_time);
    TaskId task_id_1 = task_manager.Create(task1);
    TaskId task_id_2 = task_manager.Create(task2);
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
    TaskManager task_manager;
    TaskId task_id = TaskId::Create(5);
    Task task = Task::Create("title", Task::Priority::NONE, time(0));
    // Act & Assert
    EXPECT_THROW(task_manager.Edit(task_id, task), std::invalid_argument);
}

// Giving unused TaskId to Delete method
// Should throw std::invalid argument
TEST_F(TaskManagerTest, TryDeletingNonExistentTask_ShouldThrowInvalidArgument){
    // Arrange
    TaskManager task_manager;
    TaskId task_id = TaskId::Create(5);
    // Act & Assert
    EXPECT_THROW(task_manager.Delete(task_id), std::invalid_argument);
}