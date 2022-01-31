//
// Created by Maksym Kharchenko on 25.01.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "TaskManagerService_mock.grpc.pb.h"

#include "client/GRPCClientEndPoint.h"

#include "utilities/TaskBuilder.h"
#include "utilities/TaskComparators.h"

#include <google/protobuf/util/time_util.h>

using ::testing::Return;
using ::testing::_;

class GRPCClientEndPointTest : public ::testing::Test {
public:
    Task expected_task_;
    TaskId expected_task_id_;
    TaskId expected_parent_id_;
    std::string expected_label_;
    RelationalTask expected_relational_task_;
    std::string expected_file_name_;
    void SetUp() override {
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

TEST_F(GRPCClientEndPointTest, AddTask_ShouldSendServiceRequest) {
    // Arrange
    auto stub_ptr = std::make_unique<MockTaskManagerServiceStub>();

    EXPECT_CALL(*stub_ptr, AddTask(_, _, _)).WillOnce(testing::Invoke(
            [this](::grpc::ClientContext* context, const ::AddTaskRequest& request, ::AddTaskResponse* response) -> ::grpc::Status {
                EXPECT_EQ(expected_task_, request.task());
                response->set_result(TaskManagerServiceResult::SUCCESS);
                response->set_allocated_added_task_id(new TaskId(expected_task_id_));
                return grpc::Status::OK;
            }));
    GRPCClientEndPoint controller { std::move(stub_ptr) };
    // Act
    auto actual_result = controller.AddTask(expected_task_);
    // Assert
    EXPECT_EQ(TaskActionResult::SUCCESS, actual_result.first);
    EXPECT_EQ(expected_task_id_, actual_result.second);
}

TEST_F(GRPCClientEndPointTest, AddSubTask_ShouldSendServiceRequest) {
    // Arrange
    auto stub_ptr = std::make_unique<MockTaskManagerServiceStub>();

    EXPECT_CALL(*stub_ptr, AddSubTask(_, _, _)).WillOnce(testing::Invoke(
            [this](::grpc::ClientContext* context, const ::AddSubTaskRequest& request, ::AddSubTaskResponse* response) -> ::grpc::Status {
                EXPECT_EQ(expected_task_, request.task());
                EXPECT_EQ(expected_parent_id_, request.parent_id());
                response->set_result(TaskManagerServiceResult::FAIL_INVALID_TASK);
                response->set_allocated_added_task_id(new TaskId(expected_task_id_));
                return grpc::Status::OK;
            }));
    GRPCClientEndPoint model { std::move(stub_ptr) };
    // Act
    auto actual_result = model.AddSubTask(expected_task_, expected_parent_id_);
    // Assert
    EXPECT_EQ(TaskActionResult::FAIL_INVALID_TASK, actual_result.first);
    EXPECT_EQ(expected_task_id_, actual_result.second);
}

TEST_F(GRPCClientEndPointTest, EditTask_ShouldSendServiceRequest) {
    // Arrange
    auto stub_ptr = std::make_unique<MockTaskManagerServiceStub>();

    EXPECT_CALL(*stub_ptr, EditTask(_, _, _)).WillOnce(testing::Invoke(
            [this](::grpc::ClientContext* context, const ::EditTaskRequest& request, ::EditTaskResponse* response) -> ::grpc::Status {
                EXPECT_EQ(expected_task_, request.task());
                EXPECT_EQ(expected_task_id_, request.task_id());
                response->set_result(TaskManagerServiceResult::FAIL_NO_SUCH_TASK);
                return grpc::Status::OK;
            }));
    GRPCClientEndPoint model { std::move(stub_ptr) };
    // Act
    auto actual_result = model.EditTask(expected_task_id_, expected_task_);
    // Assert
    EXPECT_EQ(TaskActionResult::FAIL_NO_SUCH_TASK, actual_result);
}

TEST_F(GRPCClientEndPointTest, DeleteTask_ShouldSendServiceRequest) {
    // Arrange
    auto stub_ptr = std::make_unique<MockTaskManagerServiceStub>();

    EXPECT_CALL(*stub_ptr, DeleteTask(_, _, _)).WillOnce(testing::Invoke(
            [this](::grpc::ClientContext* context, const ::DeleteTaskRequest& request, ::DeleteTaskResponse* response) -> ::grpc::Status {
                EXPECT_EQ(expected_task_id_, request.task_id());
                EXPECT_TRUE(request.force_delete_subtasks());
                response->set_result(TaskManagerServiceResult::FAIL_NOT_DELETED_SUBTASKS);
                return grpc::Status::OK;
            }));
    GRPCClientEndPoint model { std::move(stub_ptr) };
    // Act
    auto actual_result = model.DeleteTask(expected_task_id_, true);
    // Assert
    EXPECT_EQ(TaskActionResult::FAIL_NOT_DELETED_SUBTASKS, actual_result);
}

TEST_F(GRPCClientEndPointTest, CompleteTask_ShouldSendServiceRequest) {
    // Arrange
    auto stub_ptr = std::make_unique<MockTaskManagerServiceStub>();

    EXPECT_CALL(*stub_ptr, CompleteTask(_, _, _)).WillOnce(testing::Invoke(
            [this](::grpc::ClientContext* context, const ::CompleteTaskRequest& request, ::CompleteTaskResponse* response) -> ::grpc::Status {
                EXPECT_EQ(expected_task_id_, request.task_id());
                EXPECT_TRUE(request.force_complete_subtasks());
                response->set_result(TaskManagerServiceResult::FAIL_UNCOMPLETED_SUBTASKS);
                return grpc::Status::OK;
            }));
    GRPCClientEndPoint model { std::move(stub_ptr) };
    // Act
    auto actual_result = model.CompleteTask(expected_task_id_, true);
    // Assert
    EXPECT_EQ(TaskActionResult::FAIL_UNCOMPLETED_SUBTASKS, actual_result);
}

TEST_F(GRPCClientEndPointTest, AddTaskLabel_ShouldSendServiceRequest) {
    // Arrange
    auto stub_ptr = std::make_unique<MockTaskManagerServiceStub>();

    EXPECT_CALL(*stub_ptr, AddTaskLabel(_, _, _)).WillOnce(testing::Invoke(
            [this](::grpc::ClientContext* context, const ::AddTaskLabelRequest& request, ::AddTaskLabelResponse* response) -> ::grpc::Status {
                EXPECT_EQ(expected_task_id_, request.task_id());
                EXPECT_EQ(expected_label_, request.label());
                response->set_result(TaskManagerServiceResult::SUCCESS);
                return grpc::Status::OK;
            }));
    GRPCClientEndPoint model { std::move(stub_ptr) };
    // Act
    auto actual_result = model.AddTaskLabel(expected_task_id_, expected_label_);
    // Assert
    EXPECT_EQ(TaskActionResult::SUCCESS, actual_result);
}

TEST_F(GRPCClientEndPointTest, RemoveTaskLabel_ShouldSendServiceRequest) {
    // Arrange
    auto stub_ptr = std::make_unique<MockTaskManagerServiceStub>();

    EXPECT_CALL(*stub_ptr, RemoveTaskLabel(_, _, _)).WillOnce(testing::Invoke(
            [this](::grpc::ClientContext* context, const ::RemoveTaskLabelRequest& request, ::RemoveTaskLabelResponse* response) -> ::grpc::Status {
                EXPECT_EQ(expected_task_id_, request.task_id());
                EXPECT_EQ(expected_label_, request.label());
                response->set_result(TaskManagerServiceResult::FAIL_NO_SUCH_LABEL);
                return grpc::Status::OK;
            }));
    GRPCClientEndPoint model { std::move(stub_ptr) };
    // Act
    auto actual_result = model.RemoveTaskLabel(expected_task_id_, expected_label_);
    // Assert
    EXPECT_EQ(TaskActionResult::FAIL_NO_SUCH_LABEL, actual_result);
}

TEST_F(GRPCClientEndPointTest, GetTasks_ShouldSendServiceRequest) {
    // Arrange
    auto stub_ptr = std::make_unique<MockTaskManagerServiceStub>();
    const std::vector<RelationalTask> expected_returned_tasks { expected_relational_task_, expected_relational_task_ };

    EXPECT_CALL(*stub_ptr, GetTasks(_, _, _)).WillOnce(testing::Invoke(
            [this](::grpc::ClientContext* context, const ::GetTasksRequest& request, ::GetTasksResponse* response) -> ::grpc::Status {
                response->mutable_tasks()->AddAllocated(new RelationalTask(expected_relational_task_));
                response->mutable_tasks()->AddAllocated(new RelationalTask(expected_relational_task_));
                return grpc::Status::OK;
            }));
    GRPCClientEndPoint model { std::move(stub_ptr) };
    // Act
    auto actual_result = model.GetTasks();
    // Assert
    EXPECT_EQ(expected_returned_tasks, actual_result);
}

TEST_F(GRPCClientEndPointTest, GetTask_ShouldSendServiceRequest) {
    // Arrange
    auto stub_ptr = std::make_unique<MockTaskManagerServiceStub>();

    EXPECT_CALL(*stub_ptr, GetTask(_, _, _)).WillOnce(testing::Invoke(
            [this](::grpc::ClientContext* context, const ::GetTaskRequest& request, ::GetTaskResponse* response) -> ::grpc::Status {
                EXPECT_EQ(expected_task_id_, request.task_id());
                response->set_allocated_task(new RelationalTask(expected_relational_task_));
                return grpc::Status::OK;
            }));
    GRPCClientEndPoint model { std::move(stub_ptr) };
    // Act
    auto actual_result = model.GetTask(expected_task_id_);
    // Assert
    ASSERT_TRUE(actual_result.has_value());
    EXPECT_EQ(expected_relational_task_, actual_result.value());
}

TEST_F(GRPCClientEndPointTest, GetTask_ShouldSendServiceRequestAndReturnNullOpt) {
    // Arrange
    auto stub_ptr = std::make_unique<MockTaskManagerServiceStub>();

    EXPECT_CALL(*stub_ptr, GetTask(_, _, _)).WillOnce(testing::Invoke(
            [this](::grpc::ClientContext* context, const ::GetTaskRequest& request, ::GetTaskResponse* response) -> ::grpc::Status {
                EXPECT_EQ(expected_task_id_, request.task_id());
                return grpc::Status::OK;
            }));
    GRPCClientEndPoint model { std::move(stub_ptr) };
    // Act
    auto actual_result = model.GetTask(expected_task_id_);
    // Assert
    ASSERT_FALSE(actual_result.has_value());
}

TEST_F(GRPCClientEndPointTest, LoadModelState_ShouldSendServiceRequest) {
    // Arrange
    auto stub_ptr = std::make_unique<MockTaskManagerServiceStub>();
    const std::vector<RelationalTask> expected_returned_tasks { expected_relational_task_, expected_relational_task_ };
    const bool expected_result = true;

    EXPECT_CALL(*stub_ptr, LoadTasks(_, _, _)).WillOnce(testing::Invoke(
            [this, &expected_returned_tasks, &expected_result](::grpc::ClientContext* context, const ::LoadTasksRequest& request, ::LoadTasksResponse* response) -> ::grpc::Status {
                EXPECT_EQ(expected_returned_tasks.size(), request.tasks_size());
                for (int i = 0; i < expected_returned_tasks.size(); ++i)
                    EXPECT_EQ(expected_returned_tasks[i], request.tasks(i));

                response->set_result(expected_result);
                return grpc::Status::OK;
            }));
    GRPCClientEndPoint model { std::move(stub_ptr) };
    // Act
    auto actual_result = model.LoadModelState(expected_returned_tasks);
    // Assert
    EXPECT_EQ(expected_result, actual_result);
}

TEST_F(GRPCClientEndPointTest, GetTasksByLabel_ShouldSendServiceRequest) {
    // Arrange
    auto stub_ptr = std::make_unique<MockTaskManagerServiceStub>();
    const std::vector<RelationalTask> expected_returned_tasks { expected_relational_task_, expected_relational_task_ };

    EXPECT_CALL(*stub_ptr, GetTasksByLabel(_, _, _)).WillOnce(testing::Invoke(
            [this](::grpc::ClientContext* context, const ::GetTasksByLabelRequest& request, ::GetTasksByLabelResponse* response) -> ::grpc::Status {
                EXPECT_EQ(expected_label_, request.label());
                response->mutable_tasks()->AddAllocated(new RelationalTask(expected_relational_task_));
                response->mutable_tasks()->AddAllocated(new RelationalTask(expected_relational_task_));
                return grpc::Status::OK;
            }));
    GRPCClientEndPoint model { std::move(stub_ptr) };
    // Act
    auto actual_result = model.GetTasksByLabel(expected_label_);
    // Assert
    EXPECT_EQ(expected_returned_tasks, actual_result);
}
