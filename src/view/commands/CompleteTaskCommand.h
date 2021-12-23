//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_COMPLETETASKCOMMAND_H
#define SIMPLETASKMANAGER_COMPLETETASKCOMMAND_H

#include "CommandInterface.h"
#include "Task.pb.h"
#include "controller/Controller.h"

#include <memory>

class CompleteTaskCommand : public CommandInterface {
public:
    explicit CompleteTaskCommand(const TaskId& task_id);
public:
    CommandResult Execute(const std::shared_ptr<Controller>& controller) override;
private:
    TaskId task_id_;
};


#endif //SIMPLETASKMANAGER_COMPLETETASKCOMMAND_H
