//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_DELETETASKCOMMAND_H
#define SIMPLETASKMANAGER_DELETETASKCOMMAND_H

#include "CommandInterface.h"
#include "Task.pb.h"

class DeleteTaskCommand {
public:
    DeleteTaskCommand(const TaskId& task_id);
public:
    void Execute() override;
private:
    TaskId task_id_;
};


#endif //SIMPLETASKMANAGER_DELETETASKCOMMAND_H
