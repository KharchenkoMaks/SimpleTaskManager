//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_DELETETASKCOMMAND_H
#define SIMPLETASKMANAGER_DELETETASKCOMMAND_H

#include "CommandInterface.h"
#include "Task.pb.h"
#include "controller/Controller.h"

#include <memory>

class DeleteTaskCommand : public CommandInterface {
public:
    DeleteTaskCommand(const std::shared_ptr<Controller>& controller, const TaskId& task_id);
public:
    void Execute() override;
private:
    TaskId task_id_;

    std::shared_ptr<Controller> controller_;
};


#endif //SIMPLETASKMANAGER_DELETETASKCOMMAND_H
