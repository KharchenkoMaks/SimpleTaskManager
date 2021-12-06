//
// Created by Maksym Kharchenko on 01.12.2021.
//

#ifndef SIMPLETASKMANAGER_IMODEL_H
#define SIMPLETASKMANAGER_IMODEL_H

#include "id/TaskId.h"
#include "tasks/Task.h"
#include "TaskTransfer.h"
#include "utilities/TaskActionResult.h"

#include <optional>

class IModel{
public:
    virtual std::optional<TaskId> AddTask(const Task& t) = 0;
    virtual std::optional<TaskId> AddSubTask(const Task& task, const TaskId& parent_id) = 0;
    virtual bool EditTask(const TaskId& id, const Task& t) = 0;
    virtual TaskActionResult DeleteTask(const TaskId& id, bool force_delete_subtasks = false) = 0;
    virtual TaskActionResult CompleteTask(const TaskId& id, bool force_complete_subtasks = false) = 0;
    virtual bool SetTaskLabel(const TaskId& id, const std::string& label) = 0;

    virtual std::vector<TaskTransfer> GetTasks() = 0;

    virtual std::optional<TaskTransfer> GetTask(const TaskId& task_id) = 0;

    virtual std::optional<std::vector<TaskTransfer>> GetTaskSubTasks(const TaskId& task_id) = 0;

    virtual bool IsTaskIdExist(const TaskId& task_id) = 0;

    virtual ~IModel() = default;
};

#endif //SIMPLETASKMANAGER_IMODEL_H
