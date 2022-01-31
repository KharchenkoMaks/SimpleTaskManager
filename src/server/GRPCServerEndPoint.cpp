//
// Created by Maksym Kharchenko on 24.01.2022.
//

#include "server/GRPCServerEndPoint.h"

GRPCServerEndPoint::GRPCServerEndPoint(std::unique_ptr<Model> model) :
            model_(std::move(model)) {}

grpc::Status GRPCServerEndPoint::AddTask(::grpc::ServerContext *context,
                                         const ::AddTaskRequest *request,
                                         ::AddTaskResponse *response) {
    auto model_result = model_->AddTask(request->task());
    response->set_result(CreateTaskManagerServiceResult(model_result.first));
    response->set_allocated_added_task_id(new TaskId(model_result.second));
    return grpc::Status::OK;
}

grpc::Status GRPCServerEndPoint::AddSubTask(::grpc::ServerContext *context,
                                            const ::AddSubTaskRequest *request,
                                            ::AddSubTaskResponse *response) {
    auto model_result = model_->AddSubTask(request->task(), request->parent_id());
    response->set_result(CreateTaskManagerServiceResult(model_result.first));
    response->set_allocated_added_task_id(new TaskId(model_result.second));
    return grpc::Status::OK;
}

grpc::Status GRPCServerEndPoint::EditTask(::grpc::ServerContext *context,
                                          const ::EditTaskRequest *request,
                                          ::EditTaskResponse *response) {
    auto model_result = model_->EditTask(request->task_id(), request->task());
    response->set_result(CreateTaskManagerServiceResult(model_result));
    return grpc::Status::OK;
}

grpc::Status GRPCServerEndPoint::DeleteTask(::grpc::ServerContext *context,
                                            const ::DeleteTaskRequest *request,
                                            ::DeleteTaskResponse *response) {
    auto model_result = model_->DeleteTask(request->task_id(), request->force_delete_subtasks());
    response->set_result(CreateTaskManagerServiceResult(model_result));
    return grpc::Status::OK;
}

grpc::Status GRPCServerEndPoint::CompleteTask(::grpc::ServerContext *context,
                                            const ::CompleteTaskRequest *request,
                                            ::CompleteTaskResponse *response) {
    auto model_result = model_->CompleteTask(request->task_id(), request->force_complete_subtasks());
    response->set_result(CreateTaskManagerServiceResult(model_result));
    return grpc::Status::OK;
}

grpc::Status GRPCServerEndPoint::AddTaskLabel(::grpc::ServerContext *context,
                                              const ::AddTaskLabelRequest *request,
                                              ::AddTaskLabelResponse *response) {
    auto model_result = model_->AddTaskLabel(request->task_id(), request->label());
    response->set_result(CreateTaskManagerServiceResult(model_result));
    return grpc::Status::OK;
}

grpc::Status GRPCServerEndPoint::RemoveTaskLabel(::grpc::ServerContext *context,
                                                 const ::RemoveTaskLabelRequest *request,
                                                 ::RemoveTaskLabelResponse *response) {
    auto model_result = model_->RemoveTaskLabel(request->task_id(), request->label());
    response->set_result(CreateTaskManagerServiceResult(model_result));
    return grpc::Status::OK;
}

grpc::Status GRPCServerEndPoint::GetTasks(::grpc::ServerContext *context,
                                             const ::GetTasksRequest *request,
                                             ::GetTasksResponse *response) {
    auto model_result = model_->GetTasks();
    for (const auto& task : model_result) {
        response->mutable_tasks()->AddAllocated(new RelationalTask(task));
    }
    return grpc::Status::OK;
}

grpc::Status GRPCServerEndPoint::GetTask(::grpc::ServerContext *context,
                                         const ::GetTaskRequest *request,
                                         ::GetTaskResponse *response) {
    auto model_result = model_->GetTask(request->task_id());
    if (model_result.has_value())
        response->set_allocated_task(new RelationalTask(model_result.value()));

    return grpc::Status::OK;
}

grpc::Status GRPCServerEndPoint::LoadTasks(::grpc::ServerContext *context, const ::LoadTasksRequest *request, ::LoadTasksResponse *response) {
    std::vector<RelationalTask> tasks;
    for (const auto& task : request->tasks()) {
        tasks.push_back(task);
    }
    auto model_result = model_->LoadModelState(tasks);
    response->set_result(model_result);

    return grpc::Status::OK;
}

grpc::Status GRPCServerEndPoint::GetTasksByLabel(::grpc::ServerContext *context,
                                                 const ::GetTasksByLabelRequest *request,
                                                 ::GetTasksByLabelResponse *response) {
    auto model_result = model_->GetTasksByLabel(request->label());
    for (const auto& task : model_result) {
        response->mutable_tasks()->AddAllocated(new RelationalTask(task));
    }
    return grpc::Status::OK;
}
