//
// Created by Maksym Kharchenko on 24.01.2022.
//

#ifndef SIMPLETASKMANAGER_GRPCSERVERENDPOINT_H
#define SIMPLETASKMANAGER_GRPCSERVERENDPOINT_H

#include "controller/ModelController.h"

#include "Requests.pb.h"
#include "Responses.pb.h"
#include "ModelControllerService.grpc.pb.h"

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

class GRPCServerEndPoint final : public ModelControllerService::Service {
public:
    explicit GRPCServerEndPoint(std::unique_ptr<ModelController> model_controller);

public:
    grpc::Status AddTask(::grpc::ServerContext *context, const ::AddTaskRequest *request, ::AddTaskResponse *response) override;
    grpc::Status AddSubTask(::grpc::ServerContext *context, const ::AddSubTaskRequest *request, ::AddSubTaskResponse *response) override;
    grpc::Status EditTask(::grpc::ServerContext *context, const ::EditTaskRequest *request, ::EditTaskResponse *response) override;
    grpc::Status DeleteTask(::grpc::ServerContext *context, const ::DeleteTaskRequest *request, ::DeleteTaskResponse *response) override;
    grpc::Status CompleteTask(::grpc::ServerContext *context, const ::CompleteTaskRequest *request, ::CompleteTaskResponse *response) override;
    grpc::Status AddTaskLabel(::grpc::ServerContext *context, const ::AddTaskLabelRequest *request, ::AddTaskLabelResponse *response) override;
    grpc::Status DeleteTaskWithSubTasks(::grpc::ServerContext *context, const ::DeleteTaskWithSubTasksRequest *request, ::DeleteTaskWithSubTasksResponse *response) override;
    grpc::Status CompleteTaskWithSubTasks(::grpc::ServerContext *context, const ::CompleteTaskWithSubTasksRequest *request, ::CompleteTaskWithSubTasksResponse *response) override;
    grpc::Status GetAllTasks(::grpc::ServerContext *context, const ::GetAllTasksRequest *request, ::GetAllTasksResponse *response) override;
    grpc::Status GetTask(::grpc::ServerContext *context, const ::GetTaskRequest *request, ::GetTaskResponse *response) override;
    grpc::Status SaveToFile(::grpc::ServerContext *context, const ::SaveToFileRequest *request, ::SaveToFileResponse *response) override;
    grpc::Status LoadFromFile(::grpc::ServerContext *context, const ::LoadFromFileRequest *request, ::LoadFromFileResponse *response) override;

private:
    ControllerRequestStatus ConvertToControllerRequestStatus(const ControllerRequestResult& controller_result) const;
private:
    std::unique_ptr<ModelController> model_controller_;
};


#endif //SIMPLETASKMANAGER_GRPCSERVERENDPOINT_H
