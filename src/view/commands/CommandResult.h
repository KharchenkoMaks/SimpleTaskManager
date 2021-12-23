//
// Created by Maksym Kharchenko on 23.12.2021.
//

#ifndef SIMPLETASKMANAGER_COMMANDRESULT_H
#define SIMPLETASKMANAGER_COMMANDRESULT_H

#include "Task.pb.h"
#include "utilities/TaskActionResult.h"

#include <optional>

class CommandResult {
public:
    static CommandResult Create(TaskActionResult result);
    static CommandResult Create(const TaskId& task_id);
    static CommandResult Create(const std::vector<TaskTransfer>& tasks_to_show);
public:
    TaskActionResult GetResult() const;
    std::optional<TaskId> GetTaskId() const;
    std::vector<TaskTransfer> GetTasksToShow() const;
private:
    TaskActionResult result_;
    std::optional<TaskId> task_id_;
    std::vector<TaskTransfer> tasks_to_show_;
};


#endif //SIMPLETASKMANAGER_COMMANDRESULT_H
