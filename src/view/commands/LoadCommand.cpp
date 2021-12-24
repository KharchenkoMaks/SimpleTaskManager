//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "LoadCommand.h"

LoadCommand::LoadCommand(const std::string& file_name) :
                         file_name_(file_name) {

}

CommandResult LoadCommand::Execute(const std::shared_ptr<Controller>& controller) {
    auto load_tasks_result = controller->LoadFromFile(file_name_);
    return CommandResult::Create(load_tasks_result);
}
