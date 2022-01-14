//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_SAVECOMMAND_H
#define SIMPLETASKMANAGER_SAVECOMMAND_H

#include "Command.h"
#include "controller/ModelController.h"

#include <memory>
#include <string>

class SaveCommand : public Command {
public:
    SaveCommand(const std::string& file_name);
public:
    CommandResult Execute(const std::shared_ptr<ModelController>& controller) override;
private:
    std::string file_name_;
};


#endif //SIMPLETASKMANAGER_SAVECOMMAND_H
