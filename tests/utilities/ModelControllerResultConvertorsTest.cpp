//
// Created by Maksym Kharchenko on 26.01.2022.
//

#include "gtest/gtest.h"

#include "utilities/ModelControllerResultConvertors.h"

#include <vector>
#include <utility>

class ModelControllerResultConvertorsTest : public ::testing::Test {
public:
    const std::vector<std::pair<ControllerRequestStatus, ControllerRequestResult>> expected_results {
            std::make_pair(ControllerRequestStatus::SUCCESS, ControllerRequestResult::SUCCESS),
            std::make_pair(ControllerRequestStatus::FILE_DAMAGED, ControllerRequestResult::FILE_DAMAGED),
            std::make_pair(ControllerRequestStatus::FILE_WAS_NOT_OPENED, ControllerRequestResult::FILE_WAS_NOT_OPENED),
            std::make_pair(ControllerRequestStatus::FAIL_UNCOMPLETED_SUBTASKS, ControllerRequestResult::FAIL_UNCOMPLETED_SUBTASKS),
            std::make_pair(ControllerRequestStatus::FAIL_NOT_DELETED_SUBTASKS, ControllerRequestResult::FAIL_NOT_DELETED_SUBTASKS),
            std::make_pair(ControllerRequestStatus::FAIL_INVALID_TASK, ControllerRequestResult::FAIL_INVALID_TASK),
            std::make_pair(ControllerRequestStatus::FAIL_NO_SUCH_TASK, ControllerRequestResult::FAIL_NO_SUCH_TASK)
    };
};

TEST_F(ModelControllerResultConvertorsTest, ConvertToControllerRequestResult) {
    // Act & Assert
    for (const auto& current_case : expected_results) {
        EXPECT_EQ(current_case.second, ConvertToControllerRequestResult(current_case.first));
    }
}

TEST_F(ModelControllerResultConvertorsTest, ConvertToControllerRequestStatus) {
    // Act & Assert
    for (const auto& current_case : expected_results) {
        EXPECT_EQ(current_case.first, ConvertToControllerRequestStatus(current_case.second));
    }
}
