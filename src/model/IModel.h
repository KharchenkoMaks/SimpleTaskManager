//
// Created by Maksym Kharchenko on 01.12.2021.
//

#ifndef SIMPLETASKMANAGER_IMODEL_H
#define SIMPLETASKMANAGER_IMODEL_H

#include "TaskId.h"
#include "tasks/Task.h"

#include <optional>

class IModel{
public:
    virtual std::optional<TaskId> AddTask(const Task& t) = 0;
    virtual bool EditTask(const TaskId& id, const Task& t) = 0;
    virtual bool DeleteTask(const TaskId& id) = 0;
    virtual bool CompleteTask(const TaskId& id) = 0;

    virtual std::vector<std::pair<TaskId, Task>> GetTasks() = 0;

    virtual std::optional<Task> GetTask(const TaskId& task_id) = 0;

    virtual bool IsTaskIdExist(const TaskId& task_id) = 0;

    virtual ~IModel() = default;
};

#endif //SIMPLETASKMANAGER_IMODEL_H
