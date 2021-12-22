//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_SAVECOMMAND_H
#define SIMPLETASKMANAGER_SAVECOMMAND_H

#include "CommandInterface.h"
#include "controller/Controller.h"
#include "console_io/ConsolePrinter.h"

#include <memory>
#include <string>

class SaveCommand : public CommandInterface {
public:
    SaveCommand(const std::string& file_name);
public:
    void Execute(const std::shared_ptr<Controller>& controller) override;
private:
    std::string file_name_;
};


#endif //SIMPLETASKMANAGER_SAVECOMMAND_H
