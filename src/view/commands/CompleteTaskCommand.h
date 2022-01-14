//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_COMPLETETASKCOMMAND_H
#define SIMPLETASKMANAGER_COMPLETETASKCOMMAND_H

#include "Command.h"
#include "Task.pb.h"
#include "controller/ModelController.h"

#include <memory>

class CompleteTaskCommand : public Command {
public:
    explicit CompleteTaskCommand(const TaskId& task_id, bool force_complete_subtasks);
public:
    CommandResult Execute(const std::shared_ptr<ModelController>& controller) override;
private:
    TaskId task_id_;
    bool force_complete_subtasks_;
};


#endif //SIMPLETASKMANAGER_COMPLETETASKCOMMAND_H
