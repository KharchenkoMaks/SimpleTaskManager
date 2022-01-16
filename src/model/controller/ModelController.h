//
// Created by Maksym Kharchenko on 29.11.2021.
//

#ifndef SIMPLETASKMANAGER_MODELCONTROLLER_H
#define SIMPLETASKMANAGER_MODELCONTROLLER_H

#include "Task.pb.h"
#include "Model.h"
#include "utilities/TaskValidator.h"
#include "utilities/TaskActionResult.h"
#include "utilities/SaveLoadStatus.h"
#include "ControllerRequestResult.h"
#include "persistence/PersistenceFactory.h"

#include <memory>
#include <utility>
#include <vector>

class ModelController {
public:
    ModelController(std::unique_ptr<Model> model,
               std::unique_ptr<TaskValidator> task_validator,
               std::unique_ptr<persistence::PersistenceFactory> persistence_factory);
public:
    virtual std::pair<ControllerRequestResult, TaskId> AddTask(const Task& task);
    virtual std::pair<ControllerRequestResult, TaskId> AddSubTask(const Task& task, const TaskId& parent_id);
    virtual ControllerRequestResult EditTask(const TaskId& task_id, const Task& task);
    virtual ControllerRequestResult DeleteTask(const TaskId& task_id);
    virtual ControllerRequestResult CompleteTask(const TaskId& task_id);
    virtual ControllerRequestResult AddTaskLabel(const TaskId& task_id, const std::string& label);

    virtual ControllerRequestResult DeleteTaskWithSubTasks(const TaskId& task_id);
    virtual ControllerRequestResult CompleteTaskWithSubTasks(const TaskId& task_id);

public:
    virtual std::vector<TaskTransfer> GetAllTasks();
    virtual std::optional<TaskTransfer> GetTask(const TaskId& task_id);
public:
    virtual ControllerRequestResult SaveToFile(const std::string& file_name);
    virtual ControllerRequestResult LoadFromFile(const std::string& file_name);

public:
    virtual ~ModelController() = default;
private:
    std::unique_ptr<Model> model_;
    std::unique_ptr<TaskValidator> task_validator_;
    std::unique_ptr<persistence::PersistenceFactory> persistence_factory_;
};


#endif //SIMPLETASKMANAGER_MODELCONTROLLER_H
