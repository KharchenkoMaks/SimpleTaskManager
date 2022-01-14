//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_DELETETASKCOMMAND_H
#define SIMPLETASKMANAGER_DELETETASKCOMMAND_H

#include "Command.h"
#include "Task.pb.h"
#include "controller/ModelController.h"

#include <memory>

class DeleteTaskCommand : public Command {
public:
    explicit DeleteTaskCommand(const TaskId& task_id, bool force_delete_subtasks);
public:
    CommandResult Execute(const std::shared_ptr<ModelController>& controller) override;
private:
    TaskId task_id_;
    bool force_delete_subtasks_;
};


#endif //SIMPLETASKMANAGER_DELETETASKCOMMAND_H
