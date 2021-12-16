//
// Created by Maksym Kharchenko on 29.11.2021.
//

#ifndef SIMPLETASKMANAGER_CONTROLLER_H
#define SIMPLETASKMANAGER_CONTROLLER_H

#include "Task.pb.h"
#include "abstract_model/IModel.h"
#include "utilities/TaskValidator.h"
#include "utilities/TaskActionResult.h"
#include "utilities/SaveLoadStatus.h"
#include "persistence/TasksPersistence.h"

#include <memory>
#include <utility>
#include <vector>

class Controller {
public:
    Controller(std::unique_ptr<IModel> model, std::unique_ptr<TaskValidator> task_validator);
    Controller(std::unique_ptr<IModel> model,
               std::unique_ptr<TaskValidator> task_validator,
               std::unique_ptr<persistence::TasksPersistence> tm_persistence);
public:
    virtual std::pair<TaskActionResult, std::optional<TaskId>> AddTask(const Task& task);
    virtual std::pair<TaskActionResult, std::optional<TaskId>> AddSubTask(const Task& task, const TaskId& parent_id);
    TaskActionResult EditTask(const TaskId& task_id, const Task& task);
    virtual TaskActionResult DeleteTask(const TaskId& task_id);
    TaskActionResult CompleteTask(const TaskId& task_id);
    TaskActionResult SetTaskLabel(const TaskId& task_id, const std::string& label);

    TaskActionResult DeleteTaskWithSubTasks(const TaskId& task_id);
    TaskActionResult CompleteTaskWithSubTasks(const TaskId& task_id);

public:
    virtual std::vector<TaskTransfer> GetAllTasks();
    std::optional<TaskTransfer> GetTask(const TaskId& task_id) const;
public:
    virtual persistence::SaveLoadStatus SaveToFile(const std::string& file_name);
    virtual persistence::SaveLoadStatus LoadFromFile(const std::string& file_name);

public:
    virtual ~Controller() = default;
private:
    std::unique_ptr<IModel> model_;

    std::unique_ptr<TaskValidator> task_validator_;

    std::unique_ptr<persistence::TasksPersistence> tm_persistence_;
};


#endif //SIMPLETASKMANAGER_CONTROLLER_H
