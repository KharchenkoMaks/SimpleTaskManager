//
// Created by Maksym Kharchenko on 15.12.2021.
//

#include "gtest/gtest.h"

#include "persistence/FilePersistence.h"
#include "utilities/SaveLoadStatus.h"
#include "Task.pb.h"
#include "utilities/TaskComparators.h"

#include <utility>
#include <google/protobuf/util/time_util.h>

class DISABLED_PersistenceTest : public ::testing::Test{
public:
    std::vector<RelationalTask> tasks_to_save;

    void SetUp() override {
        std::vector<std::pair<TaskId, Task>> tasks = GenerateTasks(5);
        RelationalTask task_transfer;
        task_transfer.set_allocated_task_id(new TaskId(tasks[0].first));
        task_transfer.set_allocated_task(new Task(tasks[0].second));
        tasks_to_save.push_back(task_transfer);
        task_transfer.clear_parent_id();

        task_transfer.set_allocated_task_id(new TaskId(tasks[1].first));
        task_transfer.set_allocated_task(new Task(tasks[1].second));
        task_transfer.set_allocated_parent_id(new TaskId(tasks[0].first));
        tasks_to_save.push_back(task_transfer);
        task_transfer.clear_parent_id();

        task_transfer.set_allocated_task_id(new TaskId(tasks[2].first));
        task_transfer.set_allocated_task(new Task(tasks[2].second));
        task_transfer.set_allocated_parent_id(new TaskId(tasks[0].first));
        tasks_to_save.push_back(task_transfer);
        task_transfer.clear_parent_id();

        task_transfer.set_allocated_task_id(new TaskId(tasks[3].first));
        task_transfer.set_allocated_task(new Task(tasks[3].second));
        tasks_to_save.push_back(task_transfer);
        task_transfer.clear_parent_id();

        task_transfer.set_allocated_task_id(new TaskId(tasks[4].first));
        task_transfer.set_allocated_task(new Task(tasks[4].second));
        task_transfer.set_allocated_parent_id(new TaskId(tasks[3].first));
        tasks_to_save.push_back(task_transfer);
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

TEST_F(DISABLED_PersistenceTest, FileReadWrite_ShouldWriteTasksAndReadTasksFromFile) {
    // Arrange
    const std::string file_name = "some_file";
    auto model_persistence = std::make_unique<persistence::FilePersistence>(file_name);
    // Act
    const persistence::SaveLoadStatus actual_save_answer = model_persistence->Save(tasks_to_save);
    // Assert
    ASSERT_EQ(persistence::SaveLoadStatus::SUCCESS, actual_save_answer);
    // Act
    const std::pair<persistence::SaveLoadStatus, std::vector<RelationalTask>> actual_loaded_tasks = model_persistence->Load();
    // Assert
    ASSERT_EQ(persistence::SaveLoadStatus::SUCCESS, actual_loaded_tasks.first);
    ASSERT_EQ(tasks_to_save.size(), actual_loaded_tasks.second.size());
    for (int i = 0; i < tasks_to_save.size(); ++i) {
        EXPECT_EQ(tasks_to_save[i], actual_loaded_tasks.second[i]);
    }
}