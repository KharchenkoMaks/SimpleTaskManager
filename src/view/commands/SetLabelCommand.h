//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_SETLABELCOMMAND_H
#define SIMPLETASKMANAGER_SETLABELCOMMAND_H

#include "Command.h"
#include "Task.pb.h"
#include "controller/Controller.h"

#include <string>
#include <memory>

class SetLabelCommand : public Command {
public:
    SetLabelCommand(const TaskId& task_id,
                    const std::string& label);
public:
    CommandResult Execute(const std::shared_ptr<Controller>& controller) override;
private:
    TaskId task_id_;
    std::string label_;
};


#endif //SIMPLETASKMANAGER_SETLABELCOMMAND_H
