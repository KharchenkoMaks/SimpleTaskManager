//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_LOADCOMMAND_H
#define SIMPLETASKMANAGER_LOADCOMMAND_H

#include "CommandInterface.h"
#include "controller/Controller.h"

#include <memory>
#include <string>

class LoadCommand : public CommandInterface {
public:
    LoadCommand(const std::shared_ptr<Controller>& controller, const std::string& file_name);
public:
    void Execute() override;
private:
    std::string file_name_;

    std::shared_ptr<Controller> controller_;
};


#endif //SIMPLETASKMANAGER_LOADCOMMAND_H
