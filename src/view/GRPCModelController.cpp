//
// Created by Maksym Kharchenko on 24.01.2022.
//

#include "GRPCModelController.h"

#include "Requests.pb.h"
#include "Responses.pb.h"

GRPCModelController::GRPCModelController(const std::shared_ptr<grpc::Channel>& channel) :
        stub_(ModelControllerService::NewStub(channel)) {}

std::pair<ControllerRequestResult, TaskId> GRPCModelController::AddTask(const Task& task) {
    AddTaskRequest request;
    request.set_allocated_task(new Task(task));

    AddTaskResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->AddTask(&context, request, &response);

    return std::make_pair(ConvertToControllerRequestResult(response.status()), response.added_task_id());
}

std::pair<ControllerRequestResult, TaskId> GRPCModelController::AddSubTask(const Task& task, const TaskId& parent_id) {
    AddSubTaskRequest request;
    request.set_allocated_task(new Task(task));
    request.set_allocated_parent_id(new TaskId(parent_id));

    AddSubTaskResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->AddSubTask(&context, request, &response);

    return std::make_pair(ConvertToControllerRequestResult(response.status()), response.added_task_id());
}

ControllerRequestResult GRPCModelController::EditTask(const TaskId& task_id, const Task& task) {
    EditTaskRequest request;
    request.set_allocated_task(new Task(task));
    request.set_allocated_task_id(new TaskId(task_id));

    EditTaskResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->EditTask(&context, request, &response);

    return ConvertToControllerRequestResult(response.status());
}

ControllerRequestResult GRPCModelController::DeleteTask(const TaskId& task_id) {
    DeleteTaskRequest request;
    request.set_allocated_task_id(new TaskId(task_id));

    DeleteTaskResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->DeleteTask(&context, request, &response);

    return ConvertToControllerRequestResult(response.status());
}

ControllerRequestResult GRPCModelController::CompleteTask(const TaskId& task_id) {
    CompleteTaskRequest request;
    request.set_allocated_task_id(new TaskId(task_id));

    CompleteTaskResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->CompleteTask(&context, request, &response);

    return ConvertToControllerRequestResult(response.status());
}

ControllerRequestResult GRPCModelController::AddTaskLabel(const TaskId& task_id, const std::string& label) {
    AddTaskLabelRequest request;
    request.set_allocated_task_id(new TaskId(task_id));
    request.set_label(label);

    AddTaskLabelResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->AddTaskLabel(&context, request, &response);

    return ConvertToControllerRequestResult(response.status());
}

ControllerRequestResult GRPCModelController::DeleteTaskWithSubTasks(const TaskId& task_id) {
    DeleteTaskWithSubTasksRequest request;
    request.set_allocated_task_id(new TaskId(task_id));

    DeleteTaskWithSubTasksResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->DeleteTaskWithSubTasks(&context, request, &response);

    return ConvertToControllerRequestResult(response.status());
}

ControllerRequestResult GRPCModelController::CompleteTaskWithSubTasks(const TaskId& task_id) {
    CompleteTaskWithSubTasksRequest request;
    request.set_allocated_task_id(new TaskId(task_id));

    CompleteTaskWithSubTasksResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->CompleteTaskWithSubTasks(&context, request, &response);

    return ConvertToControllerRequestResult(response.status());
}

std::vector<RelationalTask> GRPCModelController::GetAllTasks() {
    GetAllTasksRequest request;

    GetAllTasksResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->GetAllTasks(&context, request, &response);

    std::vector<RelationalTask> tasks;
    for (const auto& task : response.tasks()) {
        tasks.push_back(task);
    }
    return tasks;
}

std::optional<RelationalTask> GRPCModelController::GetTask(const TaskId& task_id) {
    GetTaskRequest request;
    request.set_allocated_task_id(new TaskId(task_id));

    GetTaskResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->GetTask(&context, request, &response);

    if (response.has_task())
        return response.task();
    else
        return std::nullopt;
}

ControllerRequestResult GRPCModelController::SaveToFile(const std::string& file_name) {
    SaveToFileRequest request;
    request.set_file_name(file_name);

    SaveToFileResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->SaveToFile(&context, request, &response);

    return ConvertToControllerRequestResult(response.status());
}

ControllerRequestResult GRPCModelController::LoadFromFile(const std::string& file_name) {
    LoadFromFileRequest request;
    request.set_file_name(file_name);

    LoadFromFileResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->LoadFromFile(&context, request, &response);

    return ConvertToControllerRequestResult(response.status());
}

ControllerRequestResult GRPCModelController::ConvertToControllerRequestResult(const ControllerRequestStatus& request_status) const {
    switch (request_status.status()) {
        case ControllerRequestStatus_Status_SUCCESS:
            return ControllerRequestResult::SUCCESS;
        case ControllerRequestStatus_Status_FAIL_NO_SUCH_TASK:
            return ControllerRequestResult::FAIL_NO_SUCH_TASK;
        case ControllerRequestStatus_Status_FAIL_UNCOMPLETED_SUBTASKS:
            return ControllerRequestResult::FAIL_UNCOMPLETED_SUBTASKS;
        case ControllerRequestStatus_Status_FAIL_NOT_DELETED_SUBTASKS:
            return ControllerRequestResult::FAIL_NOT_DELETED_SUBTASKS;
        case ControllerRequestStatus_Status_FAIL_INVALID_TASK:
            return ControllerRequestResult::FAIL_INVALID_TASK;
        case ControllerRequestStatus_Status_FILE_WAS_NOT_OPENED:
            return ControllerRequestResult::FILE_WAS_NOT_OPENED;
        default:
            return ControllerRequestResult::FILE_DAMAGED;
    }
}
