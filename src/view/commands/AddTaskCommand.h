//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_ADDTASKCOMMAND_H
#define SIMPLETASKMANAGER_ADDTASKCOMMAND_H

#include "CommandInterface.h"
#include "Task.pb.h"
#include "controller/Controller.h"
#include "console_io/ConsolePrinter.h"

#include <memory>

class AddTaskCommand : public CommandInterface {
public:
    AddTaskCommand(const Task& task);
public:
    void Execute(const std::shared_ptr<Controller>& controller) override;
private:
    Task task_;
};


#endif //SIMPLETASKMANAGER_ADDTASKCOMMAND_H
