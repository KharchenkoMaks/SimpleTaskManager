//
// Created by Maksym Kharchenko on 26.01.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "server/GRPCServerEndPoint.h"

#include "utilities/TaskBuilder.h"
#include "utilities/TaskComparators.h"

#include "../view/mocks/MockController.h"

#include <memory>
#include <utility>

using ::testing::Return;

class GRPCServerEndPointTests : public ::testing::Test {
public:
    std::unique_ptr<MockController> model_controller_;

    Task expected_task_;
    TaskId expected_task_id_;
    TaskId expected_parent_id_;
    std::string expected_label_;
    RelationalTask expected_relational_task_;
    std::string expected_file_name_;
    void SetUp() override {
        model_controller_ = std::make_unique<MockController>();

        expected_task_ = TaskBuilder::Create()
                .SetTitle("some title")
                .SetPriority(Task::Priority::Task_Priority_LOW)
                .SetDueDate(google::protobuf::util::TimeUtil::TimeTToTimestamp(1702737566))
                .BuildTask();
        expected_task_id_.set_id(15);
        expected_parent_id_.set_id(20);
        expected_label_ = "some label";
        expected_relational_task_.set_allocated_task_id(new TaskId(expected_task_id_));
        expected_relational_task_.set_allocated_task(new Task(expected_task_));
        expected_relational_task_.set_allocated_parent_id(new TaskId(expected_parent_id_));
        expected_file_name_ = "SomeFile";
    }
};

TEST_F(GRPCServerEndPointTests, AddTask_ShouldAskModelControllerToAddTaskAndReturnResult) {
    // Arrange
    const auto expected_model_result = std::make_pair(ControllerRequestResult::SUCCESS, expected_task_id_);
    EXPECT_CALL(*model_controller_, AddTask(expected_task_)).WillOnce(Return(expected_model_result));
    GRPCServerEndPoint server_end_point { std::move(model_controller_) };
    AddTaskResponse response;
    AddTaskRequest request;
    request.set_allocated_task(new Task(expected_task_));
    // Act
    const auto actual_result = server_end_point.AddTask(nullptr, &request, &response);
    // Assert
    ASSERT_TRUE(response.has_added_task_id());
    EXPECT_TRUE(actual_result.ok());
    EXPECT_EQ(ControllerRequestStatus::SUCCESS, response.status());
    EXPECT_EQ(expected_task_id_, response.added_task_id());
}

TEST_F(GRPCServerEndPointTests, AddSubTask_ShouldAskModelControllerToAddSubTaskAndReturnResult) {
    // Arrange
    const auto expected_model_result = std::make_pair(ControllerRequestResult::FAIL_NO_SUCH_TASK, expected_task_id_);
    EXPECT_CALL(*model_controller_, AddSubTask(expected_task_, expected_parent_id_)).WillOnce(Return(expected_model_result));
    GRPCServerEndPoint server_end_point { std::move(model_controller_) };
    AddSubTaskResponse response;
    AddSubTaskRequest request;
    request.set_allocated_task(new Task(expected_task_));
    request.set_allocated_parent_id(new TaskId(expected_parent_id_));
    // Act
    const auto actual_result = server_end_point.AddSubTask(nullptr, &request, &response);
    // Assert
    ASSERT_TRUE(response.has_added_task_id());
    EXPECT_TRUE(actual_result.ok());
    EXPECT_EQ(ControllerRequestStatus::FAIL_NO_SUCH_TASK, response.status());
    EXPECT_EQ(expected_task_id_, response.added_task_id());
}

TEST_F(GRPCServerEndPointTests, EditTask_ShouldAskModelControllerToEditTaskAndReturnResult) {
    // Arrange
    const auto expected_model_result = ControllerRequestResult::FAIL_INVALID_TASK;
    EXPECT_CALL(*model_controller_, EditTask(expected_task_id_, expected_task_)).WillOnce(Return(expected_model_result));
    GRPCServerEndPoint server_end_point { std::move(model_controller_) };
    EditTaskResponse response;
    EditTaskRequest request;
    request.set_allocated_task(new Task(expected_task_));
    request.set_allocated_task_id(new TaskId(expected_task_id_));
    // Act
    const auto actual_result = server_end_point.EditTask(nullptr, &request, &response);
    // Assert
    EXPECT_TRUE(actual_result.ok());
    EXPECT_EQ(ControllerRequestStatus::FAIL_INVALID_TASK, response.status());
}

TEST_F(GRPCServerEndPointTests, DeleteTask_ShouldAskModelControllerToDeleteTaskAndReturnResult) {
    // Arrange
    const auto expected_model_result = ControllerRequestResult::FAIL_NOT_DELETED_SUBTASKS;
    EXPECT_CALL(*model_controller_, DeleteTask(expected_task_id_)).WillOnce(Return(expected_model_result));
    GRPCServerEndPoint server_end_point { std::move(model_controller_) };
    DeleteTaskResponse response;
    DeleteTaskRequest request;
    request.set_allocated_task_id(new TaskId(expected_task_id_));
    // Act
    const auto actual_result = server_end_point.DeleteTask(nullptr, &request, &response);
    // Assert
    EXPECT_TRUE(actual_result.ok());
    EXPECT_EQ(ControllerRequestStatus::FAIL_NOT_DELETED_SUBTASKS, response.status());
}

TEST_F(GRPCServerEndPointTests, CompleteTask_ShouldAskModelControllerToCompleteTaskAndReturnResult) {
    // Arrange
    const auto expected_model_result = ControllerRequestResult::FAIL_UNCOMPLETED_SUBTASKS;
    EXPECT_CALL(*model_controller_, CompleteTask(expected_task_id_)).WillOnce(Return(expected_model_result));
    GRPCServerEndPoint server_end_point { std::move(model_controller_) };
    CompleteTaskResponse response;
    CompleteTaskRequest request;
    request.set_allocated_task_id(new TaskId(expected_task_id_));
    // Act
    const auto actual_result = server_end_point.CompleteTask(nullptr, &request, &response);
    // Assert
    EXPECT_TRUE(actual_result.ok());
    EXPECT_EQ(ControllerRequestStatus::FAIL_UNCOMPLETED_SUBTASKS, response.status());
}

TEST_F(GRPCServerEndPointTests, AddTaskLabel_ShouldAskModelControllerToAddTaskLabelAndReturnResult) {
    // Arrange
    const auto expected_model_result = ControllerRequestResult::SUCCESS;
    EXPECT_CALL(*model_controller_, AddTaskLabel(expected_task_id_, expected_label_)).WillOnce(Return(expected_model_result));
    GRPCServerEndPoint server_end_point { std::move(model_controller_) };
    AddTaskLabelResponse response;
    AddTaskLabelRequest request;
    request.set_allocated_task_id(new TaskId(expected_task_id_));
    request.set_label(expected_label_);
    // Act
    const auto actual_result = server_end_point.AddTaskLabel(nullptr, &request, &response);
    // Assert
    EXPECT_TRUE(actual_result.ok());
    EXPECT_EQ(ControllerRequestStatus::SUCCESS, response.status());
}

TEST_F(GRPCServerEndPointTests, DeleteTaskWithSubTasks_ShouldAskModelControllerToDeleteTaskWithSubTasksAndReturnResult) {
    // Arrange
    const auto expected_model_result = ControllerRequestResult::SUCCESS;
    EXPECT_CALL(*model_controller_, DeleteTaskWithSubTasks(expected_task_id_)).WillOnce(Return(expected_model_result));
    GRPCServerEndPoint server_end_point { std::move(model_controller_) };
    DeleteTaskWithSubTasksResponse response;
    DeleteTaskWithSubTasksRequest request;
    request.set_allocated_task_id(new TaskId(expected_task_id_));
    // Act
    const auto actual_result = server_end_point.DeleteTaskWithSubTasks(nullptr, &request, &response);
    // Assert
    EXPECT_TRUE(actual_result.ok());
    EXPECT_EQ(ControllerRequestStatus::SUCCESS, response.status());
}

TEST_F(GRPCServerEndPointTests, CompleteTaskWithSubTasks_ShouldAskModelControllerToCompleteTaskWithSubTasksAndReturnResult) {
    // Arrange
    const auto expected_model_result = ControllerRequestResult::SUCCESS;
    EXPECT_CALL(*model_controller_, CompleteTaskWithSubTasks(expected_task_id_)).WillOnce(Return(expected_model_result));
    GRPCServerEndPoint server_end_point { std::move(model_controller_) };
    CompleteTaskWithSubTasksResponse response;
    CompleteTaskWithSubTasksRequest request;
    request.set_allocated_task_id(new TaskId(expected_task_id_));
    // Act
    const auto actual_result = server_end_point.CompleteTaskWithSubTasks(nullptr, &request, &response);
    // Assert
    EXPECT_TRUE(actual_result.ok());
    EXPECT_EQ(ControllerRequestStatus::SUCCESS, response.status());
}

TEST_F(GRPCServerEndPointTests, GetAllTasks_ShouldGetAllTasksFromModelControllerAndReturnThem) {
    const std::vector<RelationalTask> expected_returned_tasks { expected_relational_task_, expected_relational_task_ };
    EXPECT_CALL(*model_controller_, GetAllTasks()).WillOnce(Return(expected_returned_tasks));
    GRPCServerEndPoint server_end_point { std::move(model_controller_) };
    GetAllTasksResponse response;
    GetAllTasksRequest request;
    // Act
    const auto actual_result = server_end_point.GetAllTasks(nullptr, &request, &response);
    const auto actual_returned_tasks = response.tasks();
    // Assert
    EXPECT_TRUE(actual_result.ok());
    ASSERT_EQ(expected_returned_tasks.size(), actual_returned_tasks.size());
    for (int i = 0; i < expected_returned_tasks.size(); ++i)
        EXPECT_EQ(expected_returned_tasks[i], actual_returned_tasks[i]);
}

TEST_F(GRPCServerEndPointTests, GetTask_ShouldGetTaskFromModelControllerAndReturnIt) {
    EXPECT_CALL(*model_controller_, GetTask(expected_task_id_)).WillOnce(Return(expected_relational_task_));
    GRPCServerEndPoint server_end_point { std::move(model_controller_) };
    GetTaskResponse response;
    GetTaskRequest request;
    request.set_allocated_task_id(new TaskId(expected_task_id_));
    // Act
    const auto actual_result = server_end_point.GetTask(nullptr, &request, &response);
    // Assert
    EXPECT_TRUE(actual_result.ok());
    ASSERT_TRUE(response.has_task());
    EXPECT_EQ(expected_relational_task_, response.task());
}

TEST_F(GRPCServerEndPointTests, SaveToFile_ShouldAskModelControllerToSaveToFileAndReturnResult) {
    // Arrange
    const auto expected_model_result = ControllerRequestResult::FILE_WAS_NOT_OPENED;
    EXPECT_CALL(*model_controller_, SaveToFile(expected_file_name_)).WillOnce(Return(expected_model_result));
    GRPCServerEndPoint server_end_point { std::move(model_controller_) };
    SaveToFileResponse response;
    SaveToFileRequest request;
    request.set_file_name(expected_file_name_);
    // Act
    const auto actual_result = server_end_point.SaveToFile(nullptr, &request, &response);
    // Assert
    EXPECT_TRUE(actual_result.ok());
    EXPECT_EQ(ControllerRequestStatus::FILE_WAS_NOT_OPENED, response.status());
}

TEST_F(GRPCServerEndPointTests, LoadFromFile_ShouldAskModelControllerToLoadFromFileAndReturnResult) {
    // Arrange
    const auto expected_model_result = ControllerRequestResult::FILE_DAMAGED;
    EXPECT_CALL(*model_controller_, LoadFromFile(expected_file_name_)).WillOnce(Return(expected_model_result));
    GRPCServerEndPoint server_end_point { std::move(model_controller_) };
    LoadFromFileResponse response;
    LoadFromFileRequest request;
    request.set_file_name(expected_file_name_);
    // Act
    const auto actual_result = server_end_point.LoadFromFile(nullptr, &request, &response);
    // Assert
    EXPECT_TRUE(actual_result.ok());
    EXPECT_EQ(ControllerRequestStatus::FILE_DAMAGED, response.status());
}
