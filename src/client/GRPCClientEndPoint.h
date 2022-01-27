//
// Created by Maksym Kharchenko on 24.01.2022.
//

#ifndef SIMPLETASKMANAGER_GRPCCLIENTENDPOINT_H
#define SIMPLETASKMANAGER_GRPCCLIENTENDPOINT_H

#include "model/Model.h"

#include "TaskManagerService.grpc.pb.h"

#include "utilities/TaskManagerResultFactoryMethods.h"

#include <grpcpp/grpcpp.h>

#include <memory>
#include <utility>

class GRPCClientEndPoint : public Model {
public:
    explicit GRPCClientEndPoint(std::unique_ptr<TaskManagerService::StubInterface> stub);

public:
    std::pair<TaskActionResult, TaskId> AddTask(const Task& task) override;
    std::pair<TaskActionResult, TaskId> AddSubTask(const Task& task, const TaskId& parent_id) override;
    TaskActionResult EditTask(const TaskId& task_id, const Task& task) override;
    TaskActionResult DeleteTask(const TaskId& task_id, bool force_delete_subtasks) override;
    TaskActionResult CompleteTask(const TaskId& task_id, bool force_complete_subtasks) override;
    TaskActionResult AddTaskLabel(const TaskId& task_id, const std::string& label) override;
    TaskActionResult RemoveTaskLabel(const TaskId& task_id, const std::string& label) override;

public:
    std::vector<RelationalTask> GetTasks() override;
    std::optional<RelationalTask> GetTask(const TaskId& task_id) override;

public:
    bool LoadModelState(const std::vector<RelationalTask>& tasks) override;

private:
    std::unique_ptr<TaskManagerService::StubInterface> stub_;
};


#endif //SIMPLETASKMANAGER_GRPCCLIENTENDPOINT_H
