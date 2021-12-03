//
// Created by Maksym Kharchenko on 02.12.2021.
//

#ifndef SIMPLETASKMANAGER_TASKTRANSFER_H
#define SIMPLETASKMANAGER_TASKTRANSFER_H

#include "tasks/Task.h"
#include "id/TaskId.h"

#include <optional>

class TaskTransfer {
public:
    static TaskTransfer Create(const TaskId& task_id,
                               const Task& task,
                               const std::optional<TaskId>& parent_id = std::nullopt);
public:
    TaskId GetTaskId() const;
    Task GetTask() const;
    std::optional<TaskId> GetParentTaskId() const;
private:
    TaskTransfer(const TaskId& task_id,
                 const Task& task,
                 const std::optional<TaskId>& parent_id);
private:
    TaskId task_id_;
    Task task_;
    std::optional<TaskId> parent_id_;
};


#endif //SIMPLETASKMANAGER_TASKTRANSFER_H
