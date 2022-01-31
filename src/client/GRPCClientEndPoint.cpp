//
// Created by Maksym Kharchenko on 24.01.2022.
//

#include "GRPCClientEndPoint.h"

#include "Requests.pb.h"
#include "Responses.pb.h"

GRPCClientEndPoint::GRPCClientEndPoint(std::unique_ptr<TaskManagerService::StubInterface> stub) :
        stub_(std::move(stub)) {}

std::pair<TaskActionResult, TaskId> GRPCClientEndPoint::AddTask(const Task& task) {
    AddTaskRequest request;
    request.set_allocated_task(new Task(task));

    AddTaskResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->AddTask(&context, request, &response);

    return std::make_pair(CreateTaskActionResult(response.result()), response.added_task_id());
}

std::pair<TaskActionResult, TaskId> GRPCClientEndPoint::AddSubTask(const Task& task, const TaskId& parent_id) {
    AddSubTaskRequest request;
    request.set_allocated_task(new Task(task));
    request.set_allocated_parent_id(new TaskId(parent_id));

    AddSubTaskResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->AddSubTask(&context, request, &response);

    return std::make_pair(CreateTaskActionResult(response.result()), response.added_task_id());
}

TaskActionResult GRPCClientEndPoint::EditTask(const TaskId& task_id, const Task& task) {
    EditTaskRequest request;
    request.set_allocated_task(new Task(task));
    request.set_allocated_task_id(new TaskId(task_id));

    EditTaskResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->EditTask(&context, request, &response);

    return CreateTaskActionResult(response.result());
}

TaskActionResult GRPCClientEndPoint::DeleteTask(const TaskId& task_id, const bool force_delete_subtasks) {
    DeleteTaskRequest request;
    request.set_allocated_task_id(new TaskId(task_id));
    request.set_force_delete_subtasks(force_delete_subtasks);

    DeleteTaskResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->DeleteTask(&context, request, &response);

    return CreateTaskActionResult(response.result());
}

TaskActionResult GRPCClientEndPoint::CompleteTask(const TaskId& task_id, const bool force_complete_subtasks) {
    CompleteTaskRequest request;
    request.set_allocated_task_id(new TaskId(task_id));
    request.set_force_complete_subtasks(force_complete_subtasks);

    CompleteTaskResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->CompleteTask(&context, request, &response);

    return CreateTaskActionResult(response.result());
}

TaskActionResult GRPCClientEndPoint::AddTaskLabel(const TaskId& task_id, const std::string& label) {
    AddTaskLabelRequest request;
    request.set_allocated_task_id(new TaskId(task_id));
    request.set_label(label);

    AddTaskLabelResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->AddTaskLabel(&context, request, &response);

    return CreateTaskActionResult(response.result());
}

TaskActionResult GRPCClientEndPoint::RemoveTaskLabel(const TaskId &task_id, const std::string &label) {
    RemoveTaskLabelRequest request;
    request.set_allocated_task_id(new TaskId(task_id));
    request.set_label(label);

    RemoveTaskLabelResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->RemoveTaskLabel(&context, request, &response);

    return CreateTaskActionResult(response.result());
}

std::vector<RelationalTask> GRPCClientEndPoint::GetTasks() {
    GetTasksRequest request;

    GetTasksResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->GetTasks(&context, request, &response);

    std::vector<RelationalTask> tasks;
    for (const auto& task : response.tasks()) {
        tasks.push_back(task);
    }
    return tasks;
}

std::optional<RelationalTask> GRPCClientEndPoint::GetTask(const TaskId& task_id) {
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

bool GRPCClientEndPoint::LoadModelState(const std::vector<RelationalTask>& tasks) {
    LoadTasksRequest request;
    for (const auto& task : tasks) {
        request.mutable_tasks()->AddAllocated(new RelationalTask(task));
    }

    LoadTasksResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->LoadTasks(&context, request, &response);

    return response.result();
}

std::vector<RelationalTask> GRPCClientEndPoint::GetTasksByLabel(const std::string& task_label) {
    GetTasksByLabelRequest request;
    request.set_label(task_label);

    GetTasksByLabelResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->GetTasksByLabel(&context, request, &response);

    std::vector<RelationalTask> tasks;
    for (const auto& task : response.tasks()) {
        tasks.push_back(task);
    }
    return tasks;
}
