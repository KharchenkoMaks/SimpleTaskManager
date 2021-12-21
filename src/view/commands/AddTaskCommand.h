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
    AddTaskCommand(const std::shared_ptr<Controller>& controller,
                   const std::shared_ptr<ConsolePrinter>& printer,
                   const Task& task);
public:
    void Execute() override;
private:
    Task task_;

    std::shared_ptr<ConsolePrinter> printer_;

    std::shared_ptr<Controller> controller_;
};


#endif //SIMPLETASKMANAGER_ADDTASKCOMMAND_H
