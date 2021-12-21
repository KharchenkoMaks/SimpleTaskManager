//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_SETLABELCOMMAND_H
#define SIMPLETASKMANAGER_SETLABELCOMMAND_H

#include "CommandInterface.h"
#include "Task.pb.h"
#include "controller/Controller.h"

#include <string>
#include <memory>

class SetLabelCommand : public CommandInterface {
public:
    SetLabelCommand(const std::shared_ptr<Controller>& controller, const TaskId& task_id, const std::string& label);
public:
    void Execute() override;
private:
    TaskId task_id_;
    std::string label_;

    std::shared_ptr<Controller> controller_;
};


#endif //SIMPLETASKMANAGER_SETLABELCOMMAND_H
