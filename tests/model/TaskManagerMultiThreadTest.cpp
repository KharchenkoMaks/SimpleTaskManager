//
// Created by Maksym Kharchenko on 22.02.2022.
//

#include "gtest/gtest.h"

#include "model/TaskManager.h"
#include "utilities/TaskBuilder.h"

#include "Task.pb.h"

#include <google/protobuf/util/time_util.h>
#include <thread>

class TaskManagerMultiThreadTest : public ::testing::Test {
public:
    void SetUp() override {
        task_ = TaskBuilder::Create()
                .SetTitle("task")
                .SetPriority(Task::Priority::Task_Priority_MEDIUM)
                .SetDueDate(google::protobuf::util::TimeUtil::TimeTToTimestamp(time(nullptr) + 10000))
                .BuildTask();

        task_manager_ = std::make_unique<TaskManager>(std::make_unique<IdGenerator>());
    }

    void AddTaskMultipleTimes(const int times) {
        for (int i = 0; i < times; ++i) {
            task_manager_->AddTask(task_);
        }
    }

    size_t CountTasksInTaskManager() {
        return task_manager_->GetTasks().size();
    }

private:
    Task task_;

    std::unique_ptr<TaskManager> task_manager_;
};

TEST_F(TaskManagerMultiThreadTest, AddingTasksInDifferentThreads_ShouldAddAllTasks) {
    // Arrange
    const int thread_count = 8;
    const int times_per_thread = 500;

    const int expected_tasks_added = thread_count * times_per_thread;

    std::vector<std::thread> threads;
    // Act
    for (int i = 0; i < thread_count; ++i) {
        std::thread t {&TaskManagerMultiThreadTest::AddTaskMultipleTimes, this, times_per_thread };
        threads.push_back(std::move(t));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    const size_t actual_tasks_count = CountTasksInTaskManager();
    // Assert
    EXPECT_EQ(expected_tasks_added, actual_tasks_count);
}
