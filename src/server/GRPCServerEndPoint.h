//
// Created by Maksym Kharchenko on 24.01.2022.
//

#ifndef SIMPLETASKMANAGER_GRPCSERVERENDPOINT_H
#define SIMPLETASKMANAGER_GRPCSERVERENDPOINT_H

#include "model/Model.h"

#include "Requests.pb.h"
#include "Responses.pb.h"
#include "TaskManagerService.grpc.pb.h"

#include "utilities/TaskManagerResultFactoryMethods.h"

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

class GRPCServerEndPoint final : public TaskManagerService::Service {
public:
    explicit GRPCServerEndPoint(std::unique_ptr<Model> model);

public:
    grpc::Status AddTask(::grpc::ServerContext *context, const ::AddTaskRequest *request, ::AddTaskResponse *response) override;
    grpc::Status AddSubTask(::grpc::ServerContext *context, const ::AddSubTaskRequest *request, ::AddSubTaskResponse *response) override;
    grpc::Status EditTask(::grpc::ServerContext *context, const ::EditTaskRequest *request, ::EditTaskResponse *response) override;
    grpc::Status DeleteTask(::grpc::ServerContext *context, const ::DeleteTaskRequest *request, ::DeleteTaskResponse *response) override;
    grpc::Status CompleteTask(::grpc::ServerContext *context, const ::CompleteTaskRequest *request, ::CompleteTaskResponse *response) override;
    grpc::Status AddTaskLabel(::grpc::ServerContext *context, const ::AddTaskLabelRequest *request, ::AddTaskLabelResponse *response) override;
    grpc::Status GetTasks(::grpc::ServerContext *context, const ::GetTasksRequest *request, ::GetTasksResponse *response) override;
    grpc::Status GetTask(::grpc::ServerContext *context, const ::GetTaskRequest *request, ::GetTaskResponse *response) override;

private:
    std::unique_ptr<Model> model_;
};


#endif //SIMPLETASKMANAGER_GRPCSERVERENDPOINT_H
