//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_ADDTASKCOMMAND_H
#define SIMPLETASKMANAGER_ADDTASKCOMMAND_H

#include "Command.h"
#include "Task.pb.h"
#include "controller/Controller.h"
#include "controller/ControllerRequestResult.h"

#include <memory>

class AddTaskCommand : public Command {
public:
    explicit AddTaskCommand(const Task& task);
public:
    CommandResult Execute(const std::shared_ptr<Controller>& controller) override;
private:
    Task task_;
};


#endif //SIMPLETASKMANAGER_ADDTASKCOMMAND_H
