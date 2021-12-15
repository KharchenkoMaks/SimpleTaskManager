//
// Created by Maksym Kharchenko on 15.12.2021.
//

#include "gtest/gtest.h"

#include "persistence/TaskManagerPersistence.h"
#include "utilities/TaskUtilities.h"
#include "Task.pb.h"

#include <utility>
#include <google/protobuf/util/time_util.h>

class PersistenceTest : public ::testing::Test{
public:
    TaskManagerPersistence::TaskManagerParameters parameters_to_save;

    void SetUp() override {
        TaskId last_id;
        last_id.set_id(42);
        parameters_to_save.last_id_ = last_id;
        std::vector<std::pair<TaskId, Task>> tasks = GenerateTasks(5);
        TaskTransfer task_transfer;
        task_transfer.set_allocated_task_id(new TaskId(tasks[0].first));
        task_transfer.set_allocated_task(new Task(tasks[0].second));
        parameters_to_save.tasks_.push_back(task_transfer);
        task_transfer.set_allocated_task_id(new TaskId(tasks[1].first));
        task_transfer.set_allocated_task(new Task(tasks[1].second));
        task_transfer.set_allocated_parent_id(new TaskId(tasks[0].first));
        parameters_to_save.tasks_.push_back(task_transfer);
        task_transfer.set_allocated_task_id(new TaskId(tasks[2].first));
        task_transfer.set_allocated_task(new Task(tasks[2].second));
        task_transfer.set_allocated_parent_id(new TaskId(tasks[0].first));
        parameters_to_save.tasks_.push_back(task_transfer);
        task_transfer.set_allocated_task_id(new TaskId(tasks[3].first));
        task_transfer.set_allocated_task(new Task(tasks[3].second));
        parameters_to_save.tasks_.push_back(task_transfer);
        task_transfer.set_allocated_task_id(new TaskId(tasks[4].first));
        task_transfer.set_allocated_task(new Task(tasks[4].second));
        task_transfer.set_allocated_parent_id(new TaskId(tasks[3].first));
        parameters_to_save.tasks_.push_back(task_transfer);
    }
private:
    std::vector<std::pair<TaskId, Task>> GenerateTasks(int count) {
        std::vector<std::pair<TaskId, Task>> tasks;
        for (int i = 0; i < count; ++i) {
            TaskId task_id;
            task_id.set_id(i);
            Task task;
            task.set_title("task" + std::to_string(i));
            task.set_priority(Task::Priority(i % 4));
            task.set_allocated_due_date(
                    new google::protobuf::Timestamp(google::protobuf::util::TimeUtil::TimeTToTimestamp(time(0))));
            tasks.push_back(std::pair(task_id, task));
        }
        return tasks;
    }
};

TEST_F(PersistenceTest, FileReadWrite_ShouldWriteTasksAndReadTasksFromFile) {
    // Arrange
    TaskManagerPersistence tm_persistence;
    const std::string file_name = "save.txt";
    // Act
    const bool actual_save_answer = tm_persistence.SaveToFile(file_name, parameters_to_save);
    // Assert
    ASSERT_TRUE(actual_save_answer);
    // Act
    const TaskManagerPersistence::TaskManagerParameters actual_loaded_parameters =
            tm_persistence.LoadFromFile(file_name);
    // Assert
    EXPECT_EQ(parameters_to_save.last_id_, actual_loaded_parameters.last_id_);
    EXPECT_EQ(parameters_to_save.tasks_, actual_loaded_parameters.tasks_);
}