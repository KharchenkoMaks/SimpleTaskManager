//
// Created by Maksym Kharchenko on 25.01.2022.
//

#ifndef SIMPLETASKMANAGER_MOCKMODELCONTROLLERSERVICESTUB_H
#define SIMPLETASKMANAGER_MOCKMODELCONTROLLERSERVICESTUB_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "ModelControllerService.grpc.pb.h"

class MockModelControllerServiceStub : public ModelControllerService::StubInterface {
public:
    MOCK_METHOD(::grpc::Status, AddTask, (::grpc::ClientContext* context, const ::AddTaskRequest& request, ::AddTaskResponse* response), (override));
    MOCK_METHOD(::grpc::Status, AddSubTask, (::grpc::ClientContext* context, const ::AddSubTaskRequest& request, ::AddSubTaskResponse* response), (override));
    MOCK_METHOD(::grpc::Status, EditTask, (::grpc::ClientContext* context, const ::EditTaskRequest& request, ::EditTaskResponse* response), (override));
    MOCK_METHOD(::grpc::Status, DeleteTask, (::grpc::ClientContext* context, const ::DeleteTaskRequest& request, ::DeleteTaskResponse* response), (override));
    MOCK_METHOD(::grpc::Status, CompleteTask, (::grpc::ClientContext* context, const ::CompleteTaskRequest& request, ::CompleteTaskResponse* response), (override));
    MOCK_METHOD(::grpc::Status, AddTaskLabel, (::grpc::ClientContext* context, const ::AddTaskLabelRequest& request, ::AddTaskLabelResponse* response), (override));
    MOCK_METHOD(::grpc::Status, DeleteTaskWithSubTasks, (::grpc::ClientContext* context, const ::DeleteTaskWithSubTasksRequest& request, ::DeleteTaskWithSubTasksResponse* response), (override));
    MOCK_METHOD(::grpc::Status, CompleteTaskWithSubTasks, (::grpc::ClientContext* context, const ::CompleteTaskWithSubTasksRequest& request, ::CompleteTaskWithSubTasksResponse* response), (override));
    MOCK_METHOD(::grpc::Status, GetAllTasks, (::grpc::ClientContext* context, const ::GetAllTasksRequest& request, ::GetAllTasksResponse* response), (override));
    MOCK_METHOD(::grpc::Status, GetTask, (::grpc::ClientContext* context, const ::GetTaskRequest& request, ::GetTaskResponse* response), (override));
    MOCK_METHOD(::grpc::Status, SaveToFile, (::grpc::ClientContext* context, const ::SaveToFileRequest& request, ::SaveToFileResponse* response), (override));
    MOCK_METHOD(::grpc::Status, LoadFromFile, (::grpc::ClientContext* context, const ::LoadFromFileRequest& request, ::LoadFromFileResponse* response), (override));
};

#endif //SIMPLETASKMANAGER_MOCKMODELCONTROLLERSERVICESTUB_H
