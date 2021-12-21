//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_EDITTASKCOMMAND_H
#define SIMPLETASKMANAGER_EDITTASKCOMMAND_H

#include "CommandInterface.h"
#include "Task.pb.h"

class EditTaskCommand : public CommandInterface {
public:
    EditTaskCommand(const Task& task, const TaskId& task_id);
public:
    void Execute() override;
private:
    Task task_;
    TaskId task_id_;
};


#endif //SIMPLETASKMANAGER_EDITTASKCOMMAND_H
