//
// Created by Maksym Kharchenko on 29.11.2021.
//

#ifndef SIMPLETASKMANAGER_CONTROLLER_H
#define SIMPLETASKMANAGER_CONTROLLER_H

#include "id/TaskId.h"
#include "tasks/Task.h"
#include "abstract_model/IModel.h"
#include "utilities/TaskValidator.h"
#include "utilities/TaskActionResult.h"

#include <memory>
#include <utility>
#include <vector>

class Controller {
public:
    Controller(std::unique_ptr<IModel> model, std::unique_ptr<TaskValidator> task_validator);
public:
    virtual std::pair<TaskActionResult, std::optional<TaskId>> AddTask(const Task& task);
    virtual std::pair<TaskActionResult, std::optional<TaskId>> AddSubTask(const Task& task, const TaskId& parent_id);
    TaskActionResult EditTask(const TaskId& task_id, const Task& task);
    TaskActionResult DeleteTask(const TaskId& task_id);
    TaskActionResult CompleteTask(const TaskId& task_id);
    TaskActionResult SetTaskLabel(const TaskId& task_id, const std::string& label);

    TaskActionResult DeleteTaskWithSubTasks(const TaskId& task_id);
    TaskActionResult CompleteTaskWithSubTasks(const TaskId& task_id);

public:
    virtual std::string GetAllTasks();
    std::optional<Task> GetTask(const TaskId& task_id) const;

public:
    virtual ~Controller() = default;
private:
    std::unique_ptr<IModel> model_;

    std::unique_ptr<TaskValidator> task_validator_;
};


#endif //SIMPLETASKMANAGER_CONTROLLER_H
