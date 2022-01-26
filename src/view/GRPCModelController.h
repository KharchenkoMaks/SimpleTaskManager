//
// Created by Maksym Kharchenko on 24.01.2022.
//

#ifndef SIMPLETASKMANAGER_GRPCMODELCONTROLLER_H
#define SIMPLETASKMANAGER_GRPCMODELCONTROLLER_H

#include "model/controller/ModelController.h"

#include "ModelControllerService.grpc.pb.h"

#include "utilities/ModelControllerResultConvertors.h"

#include <grpcpp/grpcpp.h>

#include <memory>
#include <utility>

class GRPCModelController : public ModelController {
public:
    explicit GRPCModelController(std::unique_ptr<ModelControllerService::StubInterface> stub);

public:
    std::pair<ControllerRequestResult, TaskId> AddTask(const Task& task) override;
    std::pair<ControllerRequestResult, TaskId> AddSubTask(const Task& task, const TaskId& parent_id) override;
    ControllerRequestResult EditTask(const TaskId& task_id, const Task& task) override;
    ControllerRequestResult DeleteTask(const TaskId& task_id) override;
    ControllerRequestResult CompleteTask(const TaskId& task_id) override;
    ControllerRequestResult AddTaskLabel(const TaskId& task_id, const std::string& label) override;

    ControllerRequestResult DeleteTaskWithSubTasks(const TaskId& task_id) override;
    ControllerRequestResult CompleteTaskWithSubTasks(const TaskId& task_id) override;

public:
    std::vector<RelationalTask> GetAllTasks() override;
    std::optional<RelationalTask> GetTask(const TaskId& task_id) override;
public:
    ControllerRequestResult SaveToFile(const std::string& file_name) override;
    ControllerRequestResult LoadFromFile(const std::string& file_name) override;

private:
    std::unique_ptr<ModelControllerService::StubInterface> stub_;
};


#endif //SIMPLETASKMANAGER_GRPCMODELCONTROLLER_H
