//
// Created by Maksym Kharchenko on 17.01.2022.
//

#ifndef SIMPLETASKMANAGER_REMOVELABELCOMMAND_H
#define SIMPLETASKMANAGER_REMOVELABELCOMMAND_H

#include "Command.h"
#include "Task.pb.h"
#include "controller/ModelController.h"

#include <string>
#include <memory>

class RemoveLabelCommand : public Command {
public:
    RemoveLabelCommand(const TaskId& task_id, const std::string& label);
public:
    CommandResult Execute(const std::shared_ptr<ModelController>& controller) override;
private:
    TaskId task_id_;
    std::string label_;
};


#endif //SIMPLETASKMANAGER_REMOVELABELCOMMAND_H
