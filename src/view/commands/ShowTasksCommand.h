//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_SHOWTASKSCOMMAND_H
#define SIMPLETASKMANAGER_SHOWTASKSCOMMAND_H

#include "CommandInterface.h"
#include "Task.pb.h"
#include "controller/Controller.h"
#include "console_io/ConsolePrinter.h"

#include <memory>

class ShowTasksCommand : public CommandInterface {
public:
    ShowTasksCommand();
public:
    void Execute(const std::shared_ptr<Controller>& controller) override;
};


#endif //SIMPLETASKMANAGER_SHOWTASKSCOMMAND_H
