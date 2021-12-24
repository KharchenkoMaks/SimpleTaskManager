//
// Created by Maksym Kharchenko on 23.12.2021.
//

#include "CommandResult.h"

CommandResult CommandResult::Create(const ControllerRequestResult result) {
    CommandResult cmd_result;
    cmd_result.result_ = result;
    return cmd_result;
}

CommandResult CommandResult::Create(const TaskId& task_id) {
    CommandResult cmd_result;
    cmd_result.result_ = ControllerRequestResult::SUCCESS;
    cmd_result.task_id_ = task_id;
    return cmd_result;
}

CommandResult CommandResult::Create(const std::vector<TaskTransfer>& tasks_to_show) {
    CommandResult cmd_result;
    cmd_result.result_ = ControllerRequestResult::SUCCESS;
    cmd_result.tasks_to_show_ = tasks_to_show;
    return cmd_result;
}

ControllerRequestResult CommandResult::GetResult() const {
    return result_;
}

std::optional<TaskId> CommandResult::GetTaskId() const {
    return task_id_;
}

std::vector<TaskTransfer> CommandResult::GetTasksToShow() const {
    return tasks_to_show_;
}
