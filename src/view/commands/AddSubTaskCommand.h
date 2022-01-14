//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_ADDSUBTASKCOMMAND_H
#define SIMPLETASKMANAGER_ADDSUBTASKCOMMAND_H

#include "Command.h"
#include "Task.pb.h"
#include "controller/ModelController.h"
#include "controller/ControllerRequestResult.h"

#include <memory>

class AddSubTaskCommand : public Command {
public:
    AddSubTaskCommand(const Task& task,
                      const TaskId& parent_id);
public:
    CommandResult Execute(const std::shared_ptr<ModelController>& controller) override;
private:
    Task task_;
    TaskId task_parent_id_;
};


#endif //SIMPLETASKMANAGER_ADDSUBTASKCOMMAND_H
