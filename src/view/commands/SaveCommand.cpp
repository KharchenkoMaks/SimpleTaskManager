//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "SaveCommand.h"

SaveCommand::SaveCommand(const std::string& file_name) :
                         file_name_(file_name) {

}

CommandResult SaveCommand::Execute(const std::shared_ptr<ModelController>& controller) {
    auto save_tasks_result = controller->SaveToFile(file_name_);
    return CommandResult::Create(save_tasks_result);
}
