//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "ShowTasksCommand.h"

ShowTasksCommand::ShowTasksCommand(const std::string& task_label) : task_label_(task_label) { }

CommandResult ShowTasksCommand::Execute(const std::shared_ptr<ModelController>& controller) {
    if (task_label_.empty())
        return CommandResult::Create(controller->GetAllTasks(), true);
    else
        return CommandResult::Create(controller->GetTasksByLabel(task_label_), false);
}
