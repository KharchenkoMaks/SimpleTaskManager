//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "ShowTasksCommand.h"

ShowTasksCommand::ShowTasksCommand() = default;

CommandResult ShowTasksCommand::Execute(const std::shared_ptr<Controller>& controller) {
    auto tasks = controller->GetAllTasks();
    return CommandResult::Create(tasks);
}
