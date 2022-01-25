//
// Created by Maksym Kharchenko on 25.01.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "ModelControllerService_mock.grpc.pb.h"

#include "view/GRPCModelController.h"

#include "utilities/TaskBuilder.h"
#include "utilities/TaskComparators.h"

#include <google/protobuf/util/time_util.h>

using ::testing::Return;
using ::testing::_;

class GRPCModelControllerTest : public ::testing::Test {
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

TEST_F(GRPCModelControllerTest, AddTask_ShouldSendServiceRequest) {
    // Arrange
    auto stub_ptr = std::make_unique<MockModelControllerServiceStub>();

    EXPECT_CALL(*stub_ptr, AddTask(_, _, _)).WillOnce(testing::Invoke(
            [this](::grpc::ClientContext* context, const ::AddTaskRequest& request, ::AddTaskResponse* response) -> ::grpc::Status {
                EXPECT_EQ(expected_task_, request.task());
                response->set_status(ControllerRequestStatus::SUCCESS);
                response->set_allocated_added_task_id(new TaskId(expected_task_id_));
                return grpc::Status::OK;
            }));
    GRPCModelController controller { std::move(stub_ptr) };
    // Act
    auto actual_result = controller.AddTask(expected_task_);
    // Assert
    EXPECT_EQ(ControllerRequestResult::SUCCESS, actual_result.first);
    EXPECT_EQ(expected_task_id_, actual_result.second);
}

TEST_F(GRPCModelControllerTest, AddSubTask_ShouldSendServiceRequest) {
    // Arrange
    auto stub_ptr = std::make_unique<MockModelControllerServiceStub>();

    EXPECT_CALL(*stub_ptr, AddSubTask(_, _, _)).WillOnce(testing::Invoke(
            [this](::grpc::ClientContext* context, const ::AddSubTaskRequest& request, ::AddSubTaskResponse* response) -> ::grpc::Status {
                EXPECT_EQ(expected_task_, request.task());
                EXPECT_EQ(expected_parent_id_, request.parent_id());
                response->set_status(ControllerRequestStatus::FAIL_INVALID_TASK);
                response->set_allocated_added_task_id(new TaskId(expected_task_id_));
                return grpc::Status::OK;
            }));
    GRPCModelController controller { std::move(stub_ptr) };
    // Act
    auto actual_result = controller.AddSubTask(expected_task_, expected_parent_id_);
    // Assert
    EXPECT_EQ(ControllerRequestResult::FAIL_INVALID_TASK, actual_result.first);
    EXPECT_EQ(expected_task_id_, actual_result.second);
}

TEST_F(GRPCModelControllerTest, EditTask_ShouldSendServiceRequest) {
    auto stub_ptr = std::make_unique<MockModelControllerServiceStub>();

    EXPECT_CALL(*stub_ptr, EditTask(_, _, _)).WillOnce(testing::Invoke(
            [this](::grpc::ClientContext* context, const ::EditTaskRequest& request, ::EditTaskResponse* response) -> ::grpc::Status {
                EXPECT_EQ(expected_task_, request.task());
                EXPECT_EQ(expected_task_id_, request.task_id());
                response->set_status(ControllerRequestStatus::FAIL_NO_SUCH_TASK);
                return grpc::Status::OK;
            }));
    GRPCModelController controller { std::move(stub_ptr) };
    // Act
    auto actual_result = controller.EditTask(expected_task_id_, expected_task_);
    // Assert
    EXPECT_EQ(ControllerRequestResult::FAIL_NO_SUCH_TASK, actual_result);
}

TEST_F(GRPCModelControllerTest, DeleteTask_ShouldSendServiceRequest) {
    auto stub_ptr = std::make_unique<MockModelControllerServiceStub>();

    EXPECT_CALL(*stub_ptr, DeleteTask(_, _, _)).WillOnce(testing::Invoke(
            [this](::grpc::ClientContext* context, const ::DeleteTaskRequest& request, ::DeleteTaskResponse* response) -> ::grpc::Status {
                EXPECT_EQ(expected_task_id_, request.task_id());
                response->set_status(ControllerRequestStatus::FAIL_NOT_DELETED_SUBTASKS);
                return grpc::Status::OK;
            }));
    GRPCModelController controller { std::move(stub_ptr) };
    // Act
    auto actual_result = controller.DeleteTask(expected_task_id_);
    // Assert
    EXPECT_EQ(ControllerRequestResult::FAIL_NOT_DELETED_SUBTASKS, actual_result);
}

TEST_F(GRPCModelControllerTest, CompleteTask_ShouldSendServiceRequest) {
    auto stub_ptr = std::make_unique<MockModelControllerServiceStub>();

    EXPECT_CALL(*stub_ptr, CompleteTask(_, _, _)).WillOnce(testing::Invoke(
            [this](::grpc::ClientContext* context, const ::CompleteTaskRequest& request, ::CompleteTaskResponse* response) -> ::grpc::Status {
                EXPECT_EQ(expected_task_id_, request.task_id());
                response->set_status(ControllerRequestStatus::FAIL_UNCOMPLETED_SUBTASKS);
                return grpc::Status::OK;
            }));
    GRPCModelController controller { std::move(stub_ptr) };
    // Act
    auto actual_result = controller.CompleteTask(expected_task_id_);
    // Assert
    EXPECT_EQ(ControllerRequestResult::FAIL_UNCOMPLETED_SUBTASKS, actual_result);
}

TEST_F(GRPCModelControllerTest, AddTaskLabel_ShouldSendServiceRequest) {
    auto stub_ptr = std::make_unique<MockModelControllerServiceStub>();

    EXPECT_CALL(*stub_ptr, AddTaskLabel(_, _, _)).WillOnce(testing::Invoke(
            [this](::grpc::ClientContext* context, const ::AddTaskLabelRequest& request, ::AddTaskLabelResponse* response) -> ::grpc::Status {
                EXPECT_EQ(expected_task_id_, request.task_id());
                EXPECT_EQ(expected_label_, request.label());
                response->set_status(ControllerRequestStatus::SUCCESS);
                return grpc::Status::OK;
            }));
    GRPCModelController controller { std::move(stub_ptr) };
    // Act
    auto actual_result = controller.AddTaskLabel(expected_task_id_, expected_label_);
    // Assert
    EXPECT_EQ(ControllerRequestResult::SUCCESS, actual_result);
}

TEST_F(GRPCModelControllerTest, DeleteTaskWithSubTasks_ShouldSendServiceRequest) {
    auto stub_ptr = std::make_unique<MockModelControllerServiceStub>();

    EXPECT_CALL(*stub_ptr, DeleteTaskWithSubTasks(_, _, _)).WillOnce(testing::Invoke(
            [this](::grpc::ClientContext* context, const ::DeleteTaskWithSubTasksRequest& request, ::DeleteTaskWithSubTasksResponse* response) -> ::grpc::Status {
                EXPECT_EQ(expected_task_id_, request.task_id());
                response->set_status(ControllerRequestStatus::SUCCESS);
                return grpc::Status::OK;
            }));
    GRPCModelController controller { std::move(stub_ptr) };
    // Act
    auto actual_result = controller.DeleteTaskWithSubTasks(expected_task_id_);
    // Assert
    EXPECT_EQ(ControllerRequestResult::SUCCESS, actual_result);
}

TEST_F(GRPCModelControllerTest, CompleteTaskWithSubTasks_ShouldSendServiceRequest) {
    auto stub_ptr = std::make_unique<MockModelControllerServiceStub>();

    EXPECT_CALL(*stub_ptr, CompleteTaskWithSubTasks(_, _, _)).WillOnce(testing::Invoke(
            [this](::grpc::ClientContext* context, const ::CompleteTaskWithSubTasksRequest& request, ::CompleteTaskWithSubTasksResponse* response) -> ::grpc::Status {
                EXPECT_EQ(expected_task_id_, request.task_id());
                response->set_status(ControllerRequestStatus::FAIL_NO_SUCH_TASK);
                return grpc::Status::OK;
            }));
    GRPCModelController controller { std::move(stub_ptr) };
    // Act
    auto actual_result = controller.CompleteTaskWithSubTasks(expected_task_id_);
    // Assert
    EXPECT_EQ(ControllerRequestResult::FAIL_NO_SUCH_TASK, actual_result);
}

TEST_F(GRPCModelControllerTest, GetAllTasks_ShouldSendServiceRequest) {
    auto stub_ptr = std::make_unique<MockModelControllerServiceStub>();
    const std::vector<RelationalTask> expected_returned_tasks { expected_relational_task_, expected_relational_task_ };

    EXPECT_CALL(*stub_ptr, GetAllTasks(_, _, _)).WillOnce(testing::Invoke(
            [this](::grpc::ClientContext* context, const ::GetAllTasksRequest& request, ::GetAllTasksResponse* response) -> ::grpc::Status {
                response->mutable_tasks()->AddAllocated(new RelationalTask(expected_relational_task_));
                response->mutable_tasks()->AddAllocated(new RelationalTask(expected_relational_task_));
                return grpc::Status::OK;
            }));
    GRPCModelController controller { std::move(stub_ptr) };
    // Act
    auto actual_result = controller.GetAllTasks();
    // Assert
    EXPECT_EQ(expected_returned_tasks, actual_result);
}

TEST_F(GRPCModelControllerTest, GetTask_ShouldSendServiceRequest) {
    auto stub_ptr = std::make_unique<MockModelControllerServiceStub>();

    EXPECT_CALL(*stub_ptr, GetTask(_, _, _)).WillOnce(testing::Invoke(
            [this](::grpc::ClientContext* context, const ::GetTaskRequest& request, ::GetTaskResponse* response) -> ::grpc::Status {
                EXPECT_EQ(expected_task_id_, request.task_id());
                response->set_allocated_task(new RelationalTask(expected_relational_task_));
                return grpc::Status::OK;
            }));
    GRPCModelController controller { std::move(stub_ptr) };
    // Act
    auto actual_result = controller.GetTask(expected_task_id_);
    // Assert
    ASSERT_TRUE(actual_result.has_value());
    EXPECT_EQ(expected_relational_task_, actual_result.value());
}

TEST_F(GRPCModelControllerTest, GetTask_ShouldSendServiceRequestAndReturnNullOpt) {
    auto stub_ptr = std::make_unique<MockModelControllerServiceStub>();

    EXPECT_CALL(*stub_ptr, GetTask(_, _, _)).WillOnce(testing::Invoke(
            [this](::grpc::ClientContext* context, const ::GetTaskRequest& request, ::GetTaskResponse* response) -> ::grpc::Status {
                EXPECT_EQ(expected_task_id_, request.task_id());
                return grpc::Status::OK;
            }));
    GRPCModelController controller { std::move(stub_ptr) };
    // Act
    auto actual_result = controller.GetTask(expected_task_id_);
    // Assert
    ASSERT_FALSE(actual_result.has_value());
}

TEST_F(GRPCModelControllerTest, SaveToFile_ShouldSendServiceRequest) {
    auto stub_ptr = std::make_unique<MockModelControllerServiceStub>();

    EXPECT_CALL(*stub_ptr, SaveToFile(_, _, _)).WillOnce(testing::Invoke(
            [this](::grpc::ClientContext* context, const ::SaveToFileRequest& request, ::SaveToFileResponse* response) -> ::grpc::Status {
                EXPECT_EQ(expected_file_name_, request.file_name());
                response->set_status(ControllerRequestStatus::FILE_DAMAGED);
                return grpc::Status::OK;
            }));
    GRPCModelController controller { std::move(stub_ptr) };
    // Act
    auto actual_result = controller.SaveToFile(expected_file_name_);
    // Assert
    EXPECT_EQ(ControllerRequestResult::FILE_DAMAGED, actual_result);
}

TEST_F(GRPCModelControllerTest, LoadFromFile_ShouldSendServiceRequest) {
    auto stub_ptr = std::make_unique<MockModelControllerServiceStub>();

    EXPECT_CALL(*stub_ptr, LoadFromFile(_, _, _)).WillOnce(testing::Invoke(
            [this](::grpc::ClientContext* context, const ::LoadFromFileRequest& request, ::LoadFromFileResponse* response) -> ::grpc::Status {
                EXPECT_EQ(expected_file_name_, request.file_name());
                response->set_status(ControllerRequestStatus::FILE_WAS_NOT_OPENED);
                return grpc::Status::OK;
            }));
    GRPCModelController controller { std::move(stub_ptr) };
    // Act
    auto actual_result = controller.LoadFromFile(expected_file_name_);
    // Assert
    EXPECT_EQ(ControllerRequestResult::FILE_WAS_NOT_OPENED, actual_result);
}
