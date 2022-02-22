//
// Created by Maksym Kharchenko on 13.11.2021.
//

#include "gtest/gtest.h"
#include "SequentIdGenerator.h"
#include "Task.pb.h"

#include <thread>
#include <mutex>

class SequentIdGeneratorTest : public ::testing::Test{

};

// Creating new TaskIds using IdGenerator
// Should return incremented TaskId
TEST_F(SequentIdGeneratorTest, CreateNewTaskId_shouldIncrementTaskId){
    // Arrange
    const int test_times = 100;
    SequentIdGenerator generator;
    // Act & Assert
    for (int expected = 1; expected < test_times; ++expected){
        TaskId task = generator.CreateNewTaskId();
        EXPECT_EQ(task.id(), expected);
    }
}

TEST_F(SequentIdGeneratorTest, SetLastTaskId_ShouldResetLastTaskId) {
    // Arrange
    const int test_times = 100;
    TaskId last_id;
    last_id.set_id(42);
    SequentIdGenerator generator;
    // Act & Assert
    generator.SetLastTaskId(last_id);
    for (int expected = last_id.id() + 1; expected < test_times + last_id.id() + 1; ++expected){
        TaskId task = generator.CreateNewTaskId();
        EXPECT_EQ(task.id(), expected);
    }
}

TEST_F(SequentIdGeneratorTest, CreateNewTaskId_ShouldWorkWithMultiThread) {
    // Arrange
    const int times_per_thread = 1000;
    const int threads_count = 5;
    std::vector<std::thread> threads;
    std::vector<int> ids_times_created(times_per_thread * threads_count + 1, 0);
    std::mutex ids_times_created_mutex;

    SequentIdGenerator generator;
    // Act
    for (int i = 0; i < threads_count; ++i) {
        std::thread t { [&](){
            for (int i = 0; i < times_per_thread; ++i) {
                auto task_id = generator.CreateNewTaskId();
                std::lock_guard<std::mutex> guard(ids_times_created_mutex);
                ids_times_created[task_id.id()]++;
            }
        }};
        threads.push_back(std::move(t));
    }
    for (int i = 0; i < threads_count; ++i) {
        threads[i].join();
    }
    // Assert
    for (int i = 1; i < ids_times_created.size(); ++i) {
        EXPECT_EQ(ids_times_created[i], 1);
    }
}
