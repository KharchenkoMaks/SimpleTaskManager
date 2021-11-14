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

    TaskId task1 = task_manager.Create(Task::Create(expected_title[0],
                                     expected_priority[0], expected_time));
    TaskId task2 = task_manager.Create(Task::Create(expected_title[1],
                                     expected_priority[1], expected_time));
    // Act
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
TEST_F(TaskManagerTest, EditingTasks_ShouldReturnEditedTask){
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