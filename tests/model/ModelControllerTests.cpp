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
#include "MockPersistence.h"

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
    RelationalTask task_transfer_;
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

        task_transfer_.set_allocated_task(new Task(expected_task_));
        task_transfer_.set_allocated_task_id(new TaskId(task_id_));
        task_transfer_.set_allocated_parent_id(new TaskId(parent_id_));
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
    // Arrange
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
    // Arrange
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
    // Arrange
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
    // Arrange
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
    // Arrange
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
    // Arrange
    const ControllerRequestResult expected_result = ControllerRequestResult::SUCCESS;
    const TaskActionResult expected_model_result = TaskActionResult::SUCCESS;

    EXPECT_CALL(*model_, DeleteTask(task_id_, true)).WillOnce(Return(expected_model_result));

    ModelController controller { std::move(model_), std::move(task_validator_), std::move(persistence_factory_) };
    // Act
    const auto actual_result = controller.DeleteTaskWithSubTasks(task_id_);
    // Assert
    EXPECT_EQ(expected_result, actual_result);
}

TEST_F(ModelControllerTests, CompleteTask_ShouldAskModelToCimpleteTaskWithNoForceTaskCompleting) {
    // Arrange
    const ControllerRequestResult expected_result = ControllerRequestResult::FAIL_UNCOMPLETED_SUBTASKS;
    const TaskActionResult expected_model_result = TaskActionResult::FAIL_UNCOMPLETED_SUBTASKS;

    EXPECT_CALL(*model_, CompleteTask(task_id_, false)).WillOnce(Return(expected_model_result));

    ModelController controller { std::move(model_), std::move(task_validator_), std::move(persistence_factory_) };
    // Act
    const auto actual_result = controller.CompleteTask(task_id_);
    // Assert
    EXPECT_EQ(expected_result, actual_result);
}

TEST_F(ModelControllerTests, CompleteTaskWithSubTasks_ShouldAskModelToCompleteTaskWithForceCompletingSubtasks) {
    // Arrange
    const ControllerRequestResult expected_result = ControllerRequestResult::SUCCESS;
    const TaskActionResult expected_model_result = TaskActionResult::SUCCESS;

    EXPECT_CALL(*model_, CompleteTask(task_id_, true)).WillOnce(Return(expected_model_result));

    ModelController controller { std::move(model_), std::move(task_validator_), std::move(persistence_factory_) };
    // Act
    const auto actual_result = controller.CompleteTaskWithSubTasks(task_id_);
    // Assert
    EXPECT_EQ(expected_result, actual_result);
}

TEST_F(ModelControllerTests, GetTask_ShouldAskModelToGetTaskWithSpecifiedIdAndReturnIt) {
    // Arrange
    const std::optional<RelationalTask> expected_result = task_transfer_;

    EXPECT_CALL(*model_, GetTask(task_id_)).WillOnce(Return(task_transfer_));

    ModelController controller { std::move(model_), std::move(task_validator_), std::move(persistence_factory_) };
    // Act
    const auto actual_result = controller.GetTask(task_id_);
    // Assert
    ASSERT_TRUE(actual_result.has_value());
    EXPECT_EQ(expected_result, actual_result);
}

TEST_F(ModelControllerTests, GetAllTasks_ShouldAskModelToGetAllTasksAndReturnVector) {
    // Arrange
    const std::vector<RelationalTask> expected_result {task_transfer_ };

    EXPECT_CALL(*model_, GetTasks()).WillOnce(Return(expected_result));

    ModelController controller { std::move(model_), std::move(task_validator_), std::move(persistence_factory_) };
    // Act
    const auto actual_result = controller.GetAllTasks();
    // Assert
    EXPECT_EQ(expected_result, actual_result);
}

TEST_F(ModelControllerTests, AddTaskLabel_ShouldAskModelToAddTaskLabelAndReturnResult) {
    // Arrange
    const ControllerRequestResult expected_result = ControllerRequestResult::SUCCESS;
    const TaskActionResult expected_model_result = TaskActionResult::SUCCESS;
    const std::string expected_label = "task label";

    EXPECT_CALL(*model_, AddTaskLabel(task_id_, expected_label)).WillOnce(Return(expected_model_result));

    ModelController controller { std::move(model_), std::move(task_validator_), std::move(persistence_factory_) };
    // Act
    const auto actual_result = controller.AddTaskLabel(task_id_, expected_label);
    // Assert
    EXPECT_EQ(expected_result, actual_result);
}

TEST_F(ModelControllerTests, SaveToFile_ShouldGetTasksFromModelAndGiveThemToFilePersistence) {
    // Arrange
    const std::vector<RelationalTask> expected_tasks_to_save {task_transfer_ };
    const std::string expected_file_name = "some_file";
    const persistence::SaveLoadStatus expected_persistence_result = persistence::SaveLoadStatus::SUCCESS;
    const ControllerRequestResult expected_result = ControllerRequestResult::SUCCESS;
    std::unique_ptr<MockPersistence> expected_persistence = std::make_unique<MockPersistence>();

    EXPECT_CALL(*model_, GetTasks()).WillOnce(Return(expected_tasks_to_save));
    EXPECT_CALL(*expected_persistence, Save(expected_tasks_to_save))
        .WillOnce(Return(expected_persistence_result));
    EXPECT_CALL(*persistence_factory_, CreateFilePersistence(expected_file_name))
        .WillOnce(Return(testing::ByMove(std::move(expected_persistence))));

    ModelController controller { std::move(model_), std::move(task_validator_), std::move(persistence_factory_) };
    // Act
    const auto actual_result = controller.SaveToFile(expected_file_name);
    // Assert
    EXPECT_EQ(expected_result, actual_result);
}

TEST_F(ModelControllerTests, LoadFromFile_ShouldLoadTasksFromPersistenceAndGiveThemToModel) {
    // Arrange
    const std::vector<RelationalTask> expected_tasks_to_save {task_transfer_ };
    const std::string expected_file_name = "some_file";
    const auto expected_persistence_result =
            std::make_pair(persistence::SaveLoadStatus::SUCCESS, expected_tasks_to_save);
    const ControllerRequestResult expected_result = ControllerRequestResult::SUCCESS;
    const bool expected_model_result = true;
    std::unique_ptr<MockPersistence> expected_persistence = std::make_unique<MockPersistence>();

    EXPECT_CALL(*model_, LoadModelState(expected_tasks_to_save))
        .WillOnce(Return(expected_model_result));
    EXPECT_CALL(*expected_persistence, Load())
            .WillOnce(Return(expected_persistence_result));
    EXPECT_CALL(*persistence_factory_, CreateFilePersistence(expected_file_name))
            .WillOnce(Return(testing::ByMove(std::move(expected_persistence))));

    ModelController controller { std::move(model_), std::move(task_validator_), std::move(persistence_factory_) };
    // Act
    const auto actual_result = controller.LoadFromFile(expected_file_name);
    // Assert
    EXPECT_EQ(expected_result, actual_result);
}

TEST_F(ModelControllerTests, LoadFromFile_ShouldReturnErrorOnPersistenceLoadError) {
    const std::string expected_file_name = "some_file";
    const auto expected_persistence_result =
            std::make_pair(persistence::SaveLoadStatus::FILE_WAS_NOT_OPENED, std::vector<RelationalTask>());
    const ControllerRequestResult expected_result = ControllerRequestResult::FILE_WAS_NOT_OPENED;
    std::unique_ptr<MockPersistence> expected_persistence = std::make_unique<MockPersistence>();

    EXPECT_CALL(*model_, LoadModelState(testing::_)).Times(0);
    EXPECT_CALL(*expected_persistence, Load())
            .WillOnce(Return(expected_persistence_result));
    EXPECT_CALL(*persistence_factory_, CreateFilePersistence(expected_file_name))
            .WillOnce(Return(testing::ByMove(std::move(expected_persistence))));

    ModelController controller { std::move(model_), std::move(task_validator_), std::move(persistence_factory_) };
    // Act
    const auto actual_result = controller.LoadFromFile(expected_file_name);
    // Assert
    EXPECT_EQ(expected_result, actual_result);
}

TEST_F(ModelControllerTests, LoadFromFile_ShouldReturnFileDamagedErrorOnModelLoadTasksError) {
    // Arrange
    const std::vector<RelationalTask> expected_tasks_to_save {task_transfer_ };
    const std::string expected_file_name = "some_file";
    const auto expected_persistence_result =
            std::make_pair(persistence::SaveLoadStatus::SUCCESS, expected_tasks_to_save);
    const ControllerRequestResult expected_result = ControllerRequestResult::FILE_DAMAGED;
    const bool expected_model_result = false;
    std::unique_ptr<MockPersistence> expected_persistence = std::make_unique<MockPersistence>();

    EXPECT_CALL(*model_, LoadModelState(expected_tasks_to_save))
            .WillOnce(Return(expected_model_result));
    EXPECT_CALL(*expected_persistence, Load())
            .WillOnce(Return(expected_persistence_result));
    EXPECT_CALL(*persistence_factory_, CreateFilePersistence(expected_file_name))
            .WillOnce(Return(testing::ByMove(std::move(expected_persistence))));

    ModelController controller { std::move(model_), std::move(task_validator_), std::move(persistence_factory_) };
    // Act
    const auto actual_result = controller.LoadFromFile(expected_file_name);
    // Assert
    EXPECT_EQ(expected_result, actual_result);
}

TEST_F(ModelControllerTests, FormControllerRequestResult_ShouldConvertTaskActionResult) {
    // Arrange
    const std::vector<TaskActionResult> expected_task_action_results {
            TaskActionResult::SUCCESS,
            TaskActionResult::FAIL_NO_SUCH_TASK,
            TaskActionResult::FAIL_INVALID_TASK,
            TaskActionResult::FAIL_UNCOMPLETED_SUBTASKS,
            TaskActionResult::FAIL_NOT_DELETED_SUBTASKS
    };
    const std::vector<ControllerRequestResult> expected_controller_results {
        ControllerRequestResult::SUCCESS,
        ControllerRequestResult::FAIL_NO_SUCH_TASK,
        ControllerRequestResult::FAIL_INVALID_TASK,
        ControllerRequestResult::FAIL_UNCOMPLETED_SUBTASKS,
        ControllerRequestResult::FAIL_NOT_DELETED_SUBTASKS
    };
    // Act & Assert
    for (int i = 0; i < expected_task_action_results.size(); ++i) {
        const auto actual_controller_result = FormControllerRequestResult(expected_task_action_results[i]);
        EXPECT_EQ(expected_controller_results[i], actual_controller_result);
    }
}

TEST_F(ModelControllerTests, FormControllerRequestResult_ShouldConvertSaveLoadStatus) {
    // Arrange
    const std::vector<persistence::SaveLoadStatus> expected_task_action_results {
            persistence::SaveLoadStatus::SUCCESS,
            persistence::SaveLoadStatus::FILE_WAS_NOT_OPENED,
            persistence::SaveLoadStatus::INVALID_FILE_STRUCTURE
    };
    const std::vector<ControllerRequestResult> expected_controller_results {
            ControllerRequestResult::SUCCESS,
            ControllerRequestResult::FILE_WAS_NOT_OPENED,
            ControllerRequestResult::FILE_DAMAGED,
    };
    // Act & Assert
    for (int i = 0; i < expected_task_action_results.size(); ++i) {
        const auto actual_controller_result = FormControllerRequestResult(expected_task_action_results[i]);
        EXPECT_EQ(expected_controller_results[i], actual_controller_result);
    }
}

TEST_F(ModelControllerTests, GetTasksByLabel_ShouldAskModelToGetTasksByLabelAndReturnVector) {
    // Arrange
    const std::vector<RelationalTask> expected_result { task_transfer_ };
    const std::string expected_label = "some label";

    EXPECT_CALL(*model_, GetTasksByLabel(expected_label)).WillOnce(Return(expected_result));

    ModelController controller { std::move(model_), std::move(task_validator_), std::move(persistence_factory_) };
    // Act
    const auto actual_result = controller.GetTasksByLabel(expected_label);
    // Assert
    EXPECT_EQ(expected_result, actual_result);
}
