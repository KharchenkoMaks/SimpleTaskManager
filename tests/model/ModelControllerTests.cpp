//
// Created by Maksym Kharchenko on 14.01.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "model/controller/ModelController.h"

#include "utilities/TaskBuilder.h"
#include "utilities/TaskComparators.h"

#include "../utilities/MockTaskValidator.h"
#include "../view/mocks/MockModel.h"
#include "MockPersistenceFactory.h"

#include <google/protobuf/util/time_util.h>
#include <utility>

using ::testing::Return;

class ModelControllerTests : public ::testing::Test {
public:
    std::unique_ptr<MockTaskValidator> task_validator_;
    std::unique_ptr<MockModel> model_;
    std::unique_ptr<MockPersistenceFactory> persistence_factory_;

    Task expected_task_;
    TaskId task_id_;
    TaskId parent_id_;
    void SetUp() override {
        task_validator_ = std::make_unique<MockTaskValidator>();
        model_ = std::make_unique<MockModel>();
        persistence_factory_ = std::make_unique<MockPersistenceFactory>();

        expected_task_ = TaskBuilder::Create()
                .SetTitle("task")
                .SetPriority(Task::Priority::Task_Priority_MEDIUM)
                .SetDueDate(google::protobuf::util::TimeUtil::TimeTToTimestamp(1000))
                .BuildTask();

        task_id_.set_id(10);
        parent_id_.set_id(42);
    }
};

TEST_F(ModelControllerTests, AddTask_ShouldAskModelToAddTaskAndReturnSuccessWithTaskId) {
    // Arrange
    const std::pair<TaskActionResult, TaskId> expected_model_result = std::make_pair(TaskActionResult::SUCCESS, task_id_);
    const std::pair<ControllerRequestResult, TaskId> expected_result = std::make_pair(ControllerRequestResult::SUCCESS, task_id_);
    const bool expected_task_validator_result = true;

    EXPECT_CALL(*task_validator_, ValidateTask(expected_task_)).WillOnce(Return(expected_task_validator_result));
    EXPECT_CALL(*model_, AddTask(expected_task_)).WillOnce(Return(expected_model_result));

    ModelController controller { std::move(model_), std::move(task_validator_), std::move(persistence_factory_) };
    // Act
    const auto actual_result = controller.AddTask(expected_task_);
    // Assert
    EXPECT_EQ(expected_result, actual_result);
}

TEST_F(ModelControllerTests, AddTask_ShouldReturnErrorOnInvalidTaskGiven) {
    const std::pair<ControllerRequestResult, TaskId> expected_result = std::make_pair(ControllerRequestResult::FAIL_INVALID_TASK, TaskId::default_instance());
    const bool expected_task_validator_result = false;

    EXPECT_CALL(*task_validator_, ValidateTask(expected_task_)).WillOnce(Return(expected_task_validator_result));

    ModelController controller { std::move(model_), std::move(task_validator_), std::move(persistence_factory_) };
    // Act
    const auto actual_result = controller.AddTask(expected_task_);
    // Assert
    EXPECT_EQ(expected_result, actual_result);
}

TEST_F(ModelControllerTests, AddSubTask_ShouldAskModelToAddSubtaskAndReturnSuccessWithTaskId) {
    // Arrange
    const std::pair<TaskActionResult, TaskId> expected_model_result = std::make_pair(TaskActionResult::SUCCESS, task_id_);
    const std::pair<ControllerRequestResult, TaskId> expected_result = std::make_pair(ControllerRequestResult::SUCCESS, task_id_);
    const bool expected_task_validator_result = true;

    EXPECT_CALL(*task_validator_, ValidateTask(expected_task_)).WillOnce(Return(expected_task_validator_result));
    EXPECT_CALL(*model_, AddSubTask(expected_task_, parent_id_)).WillOnce(Return(expected_model_result));

    ModelController controller { std::move(model_), std::move(task_validator_), std::move(persistence_factory_) };
    // Act
    const auto actual_result = controller.AddSubTask(expected_task_, parent_id_);
    // Assert
    EXPECT_EQ(expected_result, actual_result);
}

TEST_F(ModelControllerTests, AddSubTask_ShouldReturnErrorOnInvalidTaskGiven) {
    const std::pair<ControllerRequestResult, TaskId> expected_result = std::make_pair(ControllerRequestResult::FAIL_INVALID_TASK, TaskId::default_instance());
    const bool expected_task_validator_result = false;

    EXPECT_CALL(*task_validator_, ValidateTask(expected_task_)).WillOnce(Return(expected_task_validator_result));

    ModelController controller { std::move(model_), std::move(task_validator_), std::move(persistence_factory_) };
    // Act
    const auto actual_result = controller.AddSubTask(expected_task_, parent_id_);
    // Assert
    EXPECT_EQ(expected_result, actual_result);
}

TEST_F(ModelControllerTests, EditTask_ShouldAskModelToEditTaskAndReturnModelResult) {
    const ControllerRequestResult expected_result = ControllerRequestResult::SUCCESS;
    const TaskActionResult expected_model_result = TaskActionResult::SUCCESS;
    const bool expected_task_validator_result = true;

    EXPECT_CALL(*task_validator_, ValidateTask(expected_task_)).WillOnce(Return(expected_task_validator_result));
    EXPECT_CALL(*model_, EditTask(task_id_, expected_task_)).WillOnce(Return(expected_model_result));

    ModelController controller { std::move(model_), std::move(task_validator_), std::move(persistence_factory_) };
    // Act
    const auto actual_result = controller.EditTask(task_id_, expected_task_);
    // Assert
    EXPECT_EQ(expected_result, actual_result);
}

TEST_F(ModelControllerTests, EditTask_ShouldReturnErrorOnInvalidTaskGiven) {
    const ControllerRequestResult expected_result = ControllerRequestResult::FAIL_INVALID_TASK;
    const bool expected_task_validator_result = false;

    EXPECT_CALL(*task_validator_, ValidateTask(expected_task_)).WillOnce(Return(expected_task_validator_result));

    ModelController controller { std::move(model_), std::move(task_validator_), std::move(persistence_factory_) };
    // Act
    const auto actual_result = controller.EditTask(task_id_, expected_task_);
    // Assert
    EXPECT_EQ(expected_result, actual_result);
}

TEST_F(ModelControllerTests, DeleteTask_ShouldAskModelToDeleteTaskWithNoForceTaskDeleting) {
    const ControllerRequestResult expected_result = ControllerRequestResult::FAIL_NOT_DELETED_SUBTASKS;
    const TaskActionResult expected_model_result = TaskActionResult::FAIL_NOT_DELETED_SUBTASKS;

    EXPECT_CALL(*model_, DeleteTask(task_id_, false)).WillOnce(Return(expected_model_result));

    ModelController controller { std::move(model_), std::move(task_validator_), std::move(persistence_factory_) };
    // Act
    const auto actual_result = controller.DeleteTask(task_id_);
    // Assert
    EXPECT_EQ(expected_result, actual_result);
}

TEST_F(ModelControllerTests, DeleteTaskWithSubTasks_ShouldAskModelToDeleteTaskWithForceDeletingSubtasks) {
    const ControllerRequestResult expected_result = ControllerRequestResult::SUCCESS;
    const TaskActionResult expected_model_result = TaskActionResult::SUCCESS;

    EXPECT_CALL(*model_, DeleteTask(task_id_, true)).WillOnce(Return(expected_model_result));

    ModelController controller { std::move(model_), std::move(task_validator_), std::move(persistence_factory_) };
    // Act
    const auto actual_result = controller.DeleteTaskWithSubTasks(task_id_);
    // Assert
    EXPECT_EQ(expected_result, actual_result);
}
