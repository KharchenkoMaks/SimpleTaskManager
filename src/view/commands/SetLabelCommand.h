//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_SETLABELCOMMAND_H
#define SIMPLETASKMANAGER_SETLABELCOMMAND_H

#include "CommandInterface.h"
#include "Task.pb.h"

#include <string>

class SetLabelCommand : public CommandInterface {
public:
    SetLabelCommand(const TaskId& task_id, const std::string& label);
public:
    void Execute() override;
private:
    TaskId task_id;
    std::string label_;
};


#endif //SIMPLETASKMANAGER_SETLABELCOMMAND_H
