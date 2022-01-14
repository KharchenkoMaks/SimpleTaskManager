//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_LOADCOMMAND_H
#define SIMPLETASKMANAGER_LOADCOMMAND_H

#include "Command.h"
#include "controller/ModelController.h"

#include <memory>
#include <string>

class LoadCommand : public Command {
public:
    explicit LoadCommand(const std::string& file_name);
public:
    CommandResult Execute(const std::shared_ptr<ModelController>& controller) override;
private:
    std::string file_name_;
};


#endif //SIMPLETASKMANAGER_LOADCOMMAND_H
