//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "ShowTasksCommand.h"

ShowTasksCommand::ShowTasksCommand(const std::string& task_label) : task_label_(task_label) {}

CommandResult ShowTasksCommand::Execute(const std::shared_ptr<ModelController>& controller) {
    std::vector<RelationalTask> tasks;
    if (task_label_.empty()) {
        tasks = controller->GetAllTasks();
    } else {
        tasks = controller->GetTasksByLabel(task_label_);
        std::for_each(tasks.begin(), tasks.end(), [&](auto& item){
            item.clear_parent_id();
        });
    }

    return CommandResult::Create(tasks);
}
