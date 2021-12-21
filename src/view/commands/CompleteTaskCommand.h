//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_COMPLETETASKCOMMAND_H
#define SIMPLETASKMANAGER_COMPLETETASKCOMMAND_H

#include "CommandInterface.h"
#include "Task.pb.h"

class CompleteTaskCommand {
public:
    CompleteTaskCommand(const TaskId& task_id);
public:
    void Execute() override;
private:
    TaskId task_id_;
};


#endif //SIMPLETASKMANAGER_COMPLETETASKCOMMAND_H
