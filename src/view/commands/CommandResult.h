//
// Created by Maksym Kharchenko on 23.12.2021.
//

#ifndef SIMPLETASKMANAGER_COMMANDRESULT_H
#define SIMPLETASKMANAGER_COMMANDRESULT_H

#include "Task.pb.h"
#include "model/controller/ControllerRequestResult.h"

#include <optional>

class CommandResult {
public:
    static CommandResult Create(ControllerRequestResult result);
    static CommandResult Create(const TaskId& task_id);
    static CommandResult Create(const std::vector<RelationalTask>& tasks_to_show);
public:
    ControllerRequestResult GetResult() const;
    std::optional<TaskId> GetTaskId() const;
    std::vector<RelationalTask> GetTasksToShow() const;
private:
    ControllerRequestResult result_;
    std::optional<TaskId> task_id_;
    std::vector<RelationalTask> tasks_to_show_;
};


#endif //SIMPLETASKMANAGER_COMMANDRESULT_H
