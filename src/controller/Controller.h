//
// Created by Maksym Kharchenko on 29.11.2021.
//

#ifndef SIMPLETASKMANAGER_CONTROLLER_H
#define SIMPLETASKMANAGER_CONTROLLER_H

#include "id/TaskId.h"
#include "tasks/Task.h"
#include "abstract_model/IModel.h"
#include "TaskValidator.h"

#include <memory>
#include <utility>
#include <vector>

class Controller {
public:
    Controller(std::unique_ptr<IModel> model, std::unique_ptr<TaskValidator> task_validator);
public:
    std::optional<TaskId> AddTask(const Task& task);
    std::optional<TaskId> AddSubTask(const Task& task, const TaskId& parent_id);
    bool EditTask(const TaskId& task_id, const Task& task);
    bool DeleteTask(const TaskId& task_id);
    bool CompleteTask(const TaskId& task_id);

    virtual std::string GetAllTasks();
public:
    std::optional<Task> GetTask(const TaskId& task_id) const;
public:
    virtual ~Controller() = default;
private:
    std::unique_ptr<IModel> model_;

    std::unique_ptr<TaskValidator> task_validator_;
};


#endif //SIMPLETASKMANAGER_CONTROLLER_H
