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

CommandResult CommandResult::Create(const std::vector<RelationalTask>& tasks_to_show, const bool show_tasks_relations) {
    CommandResult cmd_result;
    cmd_result.result_ = ControllerRequestResult::SUCCESS;
    cmd_result.tasks_to_show_.tasks_ = tasks_to_show;
    cmd_result.tasks_to_show_.show_task_relations_ = show_tasks_relations;
    return cmd_result;
}

ControllerRequestResult CommandResult::GetResult() const {
    return result_;
}

std::optional<TaskId> CommandResult::GetTaskId() const {
    return task_id_;
}

CommandResult::TasksToShow CommandResult::GetTasksToShow() const {
    return tasks_to_show_;
}
