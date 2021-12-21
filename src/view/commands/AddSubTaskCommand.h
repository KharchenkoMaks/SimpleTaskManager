//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_ADDSUBTASKCOMMAND_H
#define SIMPLETASKMANAGER_ADDSUBTASKCOMMAND_H

#include "CommandInterface.h"
#include "Task.pb.h"
#include "controller/Controller.h"
#include "view/console_io/ConsolePrinter.h"

#include <memory>

class AddSubTaskCommand : public CommandInterface {
public:
    AddSubTaskCommand(const std::shared_ptr<Controller>& controller,
                      const std::shared_ptr<ConsolePrinter>& printer,
                      const Task& task,
                      const TaskId& parent_id);
public:
    void Execute() override;
private:
    Task task_;
    TaskId task_parent_id_;

    std::shared_ptr<ConsolePrinter> printer_;

    std::shared_ptr<Controller> controller_;
};


#endif //SIMPLETASKMANAGER_ADDSUBTASKCOMMAND_H
