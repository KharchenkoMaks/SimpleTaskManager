//
// Created by Maksym Kharchenko on 26.01.2022.
//

#include "gtest/gtest.h"

#include "utilities/TaskManagerResultFactoryMethods.h"

#include <vector>
#include <utility>

class TaskManagerResultFactoryMethodsTest : public ::testing::Test {
public:
    const std::vector<std::pair<TaskManagerServiceResult, TaskActionResult>> expected_results {
            std::make_pair(TaskManagerServiceResult::SUCCESS, TaskActionResult::SUCCESS),
            std::make_pair(TaskManagerServiceResult::FAIL_UNCOMPLETED_SUBTASKS, TaskActionResult::FAIL_UNCOMPLETED_SUBTASKS),
            std::make_pair(TaskManagerServiceResult::FAIL_NOT_DELETED_SUBTASKS, TaskActionResult::FAIL_NOT_DELETED_SUBTASKS),
            std::make_pair(TaskManagerServiceResult::FAIL_INVALID_TASK, TaskActionResult::FAIL_INVALID_TASK),
            std::make_pair(TaskManagerServiceResult::FAIL_NO_SUCH_TASK, TaskActionResult::FAIL_NO_SUCH_TASK),
            std::make_pair(TaskManagerServiceResult::FAIL_NO_SUCH_LABEL, TaskActionResult::FAIL_NO_SUCH_LABEL),
            std::make_pair(TaskManagerServiceResult::FAIL_SERVER_TROUBLES, TaskActionResult::FAIL_SERVER_TROUBLES)
    };
};

TEST_F(TaskManagerResultFactoryMethodsTest, CreateTaskActionResult) {
    // Act & Assert
    for (const auto& current_case : expected_results) {
        EXPECT_EQ(current_case.second, CreateTaskActionResult(current_case.first));
    }
}

TEST_F(TaskManagerResultFactoryMethodsTest, CreateTaskManagerServiceResult) {
    // Act & Assert
    for (const auto& current_case : expected_results) {
        EXPECT_EQ(current_case.first, CreateTaskManagerServiceResult(current_case.second));
    }
}
