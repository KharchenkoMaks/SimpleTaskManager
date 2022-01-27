//
// Created by Maksym Kharchenko on 26.01.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "server/GRPCServerEndPoint.h"

#include "utilities/TaskBuilder.h"
#include "utilities/TaskComparators.h"

#include "../view/mocks/MockModel.h"

#include <memory>
#include <utility>

using ::testing::Return;

class GRPCServerEndPointTests : public ::testing::Test {
public:
    std::unique_ptr<MockModel> model_;

    Task expected_task_;
    TaskId expected_task_id_;
    TaskId expected_parent_id_;
    std::string expected_label_;
    RelationalTask expected_relational_task_;
    std::string expected_file_name_;
    void SetUp() override {
        model_ = std::make_unique<MockModel>();

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

TEST_F(GRPCServerEndPointTests, AddTask_ShouldAskModelToAddTaskAndReturnResult) {
    // Arrange
    const auto expected_model_result = std::make_pair(TaskActionResult::SUCCESS, expected_task_id_);
    EXPECT_CALL(*model_, AddTask(expected_task_)).WillOnce(Return(expected_model_result));
    GRPCServerEndPoint server_end_point { std::move(model_) };
    AddTaskResponse response;
    AddTaskRequest request;
    request.set_allocated_task(new Task(expected_task_));
    // Act
    const auto actual_result = server_end_point.AddTask(nullptr, &request, &response);
    // Assert
    ASSERT_TRUE(response.has_added_task_id());
    EXPECT_TRUE(actual_result.ok());
    EXPECT_EQ(TaskManagerServiceResult::SUCCESS, response.result());
    EXPECT_EQ(expected_task_id_, response.added_task_id());
}

TEST_F(GRPCServerEndPointTests, AddSubTask_ShouldAskModelToAddSubTaskAndReturnResult) {
    // Arrange
    const auto expected_model_result = std::make_pair(TaskActionResult::FAIL_NO_SUCH_TASK, expected_task_id_);
    EXPECT_CALL(*model_, AddSubTask(expected_task_, expected_parent_id_)).WillOnce(Return(expected_model_result));
    GRPCServerEndPoint server_end_point { std::move(model_) };
    AddSubTaskResponse response;
    AddSubTaskRequest request;
    request.set_allocated_task(new Task(expected_task_));
    request.set_allocated_parent_id(new TaskId(expected_parent_id_));
    // Act
    const auto actual_result = server_end_point.AddSubTask(nullptr, &request, &response);
    // Assert
    ASSERT_TRUE(response.has_added_task_id());
    EXPECT_TRUE(actual_result.ok());
    EXPECT_EQ(TaskManagerServiceResult::FAIL_NO_SUCH_TASK, response.result());
    EXPECT_EQ(expected_task_id_, response.added_task_id());
}

TEST_F(GRPCServerEndPointTests, EditTask_ShouldAskModelToEditTaskAndReturnResult) {
    // Arrange
    const auto expected_model_result = TaskActionResult::FAIL_INVALID_TASK;
    EXPECT_CALL(*model_, EditTask(expected_task_id_, expected_task_)).WillOnce(Return(expected_model_result));
    GRPCServerEndPoint server_end_point { std::move(model_) };
    EditTaskResponse response;
    EditTaskRequest request;
    request.set_allocated_task(new Task(expected_task_));
    request.set_allocated_task_id(new TaskId(expected_task_id_));
    // Act
    const auto actual_result = server_end_point.EditTask(nullptr, &request, &response);
    // Assert
    EXPECT_TRUE(actual_result.ok());
    EXPECT_EQ(TaskManagerServiceResult::FAIL_INVALID_TASK, response.result());
}

TEST_F(GRPCServerEndPointTests, DeleteTask_ShouldAskModelToDeleteTaskAndReturnResult) {
    // Arrange
    const auto expected_model_result = TaskActionResult::FAIL_NOT_DELETED_SUBTASKS;
    const bool expected_force_delete = true;
    EXPECT_CALL(*model_, DeleteTask(expected_task_id_, expected_force_delete)).WillOnce(Return(expected_model_result));
    GRPCServerEndPoint server_end_point { std::move(model_) };
    DeleteTaskResponse response;
    DeleteTaskRequest request;
    request.set_allocated_task_id(new TaskId(expected_task_id_));
    request.set_force_delete_subtasks(expected_force_delete);
    // Act
    const auto actual_result = server_end_point.DeleteTask(nullptr, &request, &response);
    // Assert
    EXPECT_TRUE(actual_result.ok());
    EXPECT_EQ(TaskManagerServiceResult::FAIL_NOT_DELETED_SUBTASKS, response.result());
}

TEST_F(GRPCServerEndPointTests, CompleteTask_ShouldAskModelToCompleteTaskAndReturnResult) {
    // Arrange
    const auto expected_model_result = TaskActionResult::FAIL_UNCOMPLETED_SUBTASKS;
    const bool expected_force_complete = true;
    EXPECT_CALL(*model_, CompleteTask(expected_task_id_, expected_force_complete)).WillOnce(Return(expected_model_result));
    GRPCServerEndPoint server_end_point { std::move(model_) };
    CompleteTaskResponse response;
    CompleteTaskRequest request;
    request.set_allocated_task_id(new TaskId(expected_task_id_));
    request.set_force_complete_subtasks(expected_force_complete);
    // Act
    const auto actual_result = server_end_point.CompleteTask(nullptr, &request, &response);
    // Assert
    EXPECT_TRUE(actual_result.ok());
    EXPECT_EQ(TaskManagerServiceResult::FAIL_UNCOMPLETED_SUBTASKS, response.result());
}

TEST_F(GRPCServerEndPointTests, AddTaskLabel_ShouldAskModelToAddTaskLabelAndReturnResult) {
    // Arrange
    const auto expected_model_result = TaskActionResult::SUCCESS;
    EXPECT_CALL(*model_, AddTaskLabel(expected_task_id_, expected_label_)).WillOnce(Return(expected_model_result));
    GRPCServerEndPoint server_end_point { std::move(model_) };
    AddTaskLabelResponse response;
    AddTaskLabelRequest request;
    request.set_allocated_task_id(new TaskId(expected_task_id_));
    request.set_label(expected_label_);
    // Act
    const auto actual_result = server_end_point.AddTaskLabel(nullptr, &request, &response);
    // Assert
    EXPECT_TRUE(actual_result.ok());
    EXPECT_EQ(TaskManagerServiceResult::SUCCESS, response.result());
}

TEST_F(GRPCServerEndPointTests, GetTasks_ShouldGetTasksFromModelAndReturnThem) {
    const std::vector<RelationalTask> expected_returned_tasks { expected_relational_task_, expected_relational_task_ };
    EXPECT_CALL(*model_, GetTasks()).WillOnce(Return(expected_returned_tasks));
    GRPCServerEndPoint server_end_point { std::move(model_) };
    GetTasksResponse response;
    GetTasksRequest request;
    // Act
    const auto actual_result = server_end_point.GetTasks(nullptr, &request, &response);
    const auto actual_returned_tasks = response.tasks();
    // Assert
    EXPECT_TRUE(actual_result.ok());
    ASSERT_EQ(expected_returned_tasks.size(), actual_returned_tasks.size());
    for (int i = 0; i < expected_returned_tasks.size(); ++i)
        EXPECT_EQ(expected_returned_tasks[i], actual_returned_tasks[i]);
}

TEST_F(GRPCServerEndPointTests, GetTask_ShouldGetTaskFromModelAndReturnIt) {
    EXPECT_CALL(*model_, GetTask(expected_task_id_)).WillOnce(Return(expected_relational_task_));
    GRPCServerEndPoint server_end_point { std::move(model_) };
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
