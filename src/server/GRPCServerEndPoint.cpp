//
// Created by Maksym Kharchenko on 24.01.2022.
//

#include "server/GRPCServerEndPoint.h"

GRPCServerEndPoint::GRPCServerEndPoint(std::unique_ptr<ModelController> model_controller) :
            model_controller_(std::move(model_controller)) {}

grpc::Status GRPCServerEndPoint::AddTask(::grpc::ServerContext *context,
                                         const ::AddTaskRequest *request,
                                         ::AddTaskResponse *response) {
    auto controller_result = model_controller_->AddTask(request->task());
    response->set_status(ConvertToControllerRequestStatus(controller_result.first));
    response->set_allocated_added_task_id(new TaskId(controller_result.second));
    return grpc::Status::OK;
}

grpc::Status GRPCServerEndPoint::AddSubTask(::grpc::ServerContext *context,
                                            const ::AddSubTaskRequest *request,
                                            ::AddSubTaskResponse *response) {
    auto controller_result = model_controller_->AddSubTask(request->task(), request->parent_id());
    response->set_status(ConvertToControllerRequestStatus(controller_result.first));
    response->set_allocated_added_task_id(new TaskId(controller_result.second));
    return grpc::Status::OK;
}

grpc::Status GRPCServerEndPoint::EditTask(::grpc::ServerContext *context,
                                          const ::EditTaskRequest *request,
                                          ::EditTaskResponse *response) {
    auto controller_result = model_controller_->EditTask(request->task_id(), request->task());
    response->set_status(ConvertToControllerRequestStatus(controller_result));
    return grpc::Status::OK;
}

grpc::Status GRPCServerEndPoint::DeleteTask(::grpc::ServerContext *context,
                                            const ::DeleteTaskRequest *request,
                                            ::DeleteTaskResponse *response) {
    auto controller_result = model_controller_->DeleteTask(request->task_id());
    response->set_status(ConvertToControllerRequestStatus(controller_result));
    return grpc::Status::OK;
}

grpc::Status GRPCServerEndPoint::CompleteTask(::grpc::ServerContext *context,
                                            const ::CompleteTaskRequest *request,
                                            ::CompleteTaskResponse *response) {
    auto controller_result = model_controller_->CompleteTask(request->task_id());
    response->set_status(ConvertToControllerRequestStatus(controller_result));
    return grpc::Status::OK;
}

grpc::Status GRPCServerEndPoint::AddTaskLabel(::grpc::ServerContext *context,
                                              const ::AddTaskLabelRequest *request,
                                              ::AddTaskLabelResponse *response) {
    auto controller_result = model_controller_->AddTaskLabel(request->task_id(), request->label());
    response->set_status(ConvertToControllerRequestStatus(controller_result));
    return grpc::Status::OK;
}

grpc::Status GRPCServerEndPoint::DeleteTaskWithSubTasks(::grpc::ServerContext *context,
                                                        const ::DeleteTaskWithSubTasksRequest *request,
                                                        ::DeleteTaskWithSubTasksResponse *response) {
    auto controller_result = model_controller_->DeleteTaskWithSubTasks(request->task_id());
    response->set_status(ConvertToControllerRequestStatus(controller_result));
    return grpc::Status::OK;
}

grpc::Status GRPCServerEndPoint::CompleteTaskWithSubTasks(::grpc::ServerContext *context,
                                                        const ::CompleteTaskWithSubTasksRequest *request,
                                                        ::CompleteTaskWithSubTasksResponse *response) {
    auto controller_result = model_controller_->CompleteTaskWithSubTasks(request->task_id());
    response->set_status(ConvertToControllerRequestStatus(controller_result));
    return grpc::Status::OK;
}

grpc::Status GRPCServerEndPoint::GetAllTasks(::grpc::ServerContext *context,
                                             const ::GetAllTasksRequest *request,
                                             ::GetAllTasksResponse *response) {
    auto controller_result = model_controller_->GetAllTasks();
    for (const auto& task : controller_result) {
        response->mutable_tasks()->AddAllocated(new RelationalTask(task));
    }
    return grpc::Status::OK;
}

grpc::Status GRPCServerEndPoint::GetTask(::grpc::ServerContext *context,
                                         const ::GetTaskRequest *request,
                                         ::GetTaskResponse *response) {
    auto controller_result = model_controller_->GetTask(request->task_id());
    if (controller_result.has_value())
        response->set_allocated_task(new RelationalTask(controller_result.value()));

    return grpc::Status::OK;
}

grpc::Status GRPCServerEndPoint::SaveToFile(::grpc::ServerContext *context,
                                            const ::SaveToFileRequest *request,
                                            ::SaveToFileResponse *response) {
    auto controller_result = model_controller_->SaveToFile(request->file_name());
    response->set_status(ConvertToControllerRequestStatus(controller_result));
    return grpc::Status::OK;
}

grpc::Status GRPCServerEndPoint::LoadFromFile(::grpc::ServerContext *context,
                                              const ::LoadFromFileRequest *request,
                                              ::LoadFromFileResponse *response) {
    auto controller_result = model_controller_->LoadFromFile(request->file_name());
    response->set_status(ConvertToControllerRequestStatus(controller_result));
    return grpc::Status::OK;
}
