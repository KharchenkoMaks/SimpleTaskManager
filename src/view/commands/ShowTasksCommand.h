//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_SHOWTASKSCOMMAND_H
#define SIMPLETASKMANAGER_SHOWTASKSCOMMAND_H

#include "Command.h"
#include "Task.pb.h"
#include "controller/ModelController.h"

#include <memory>

class ShowTasksCommand : public Command {
public:
    ShowTasksCommand();
public:
    CommandResult Execute(const std::shared_ptr<ModelController>& controller) override;
};


#endif //SIMPLETASKMANAGER_SHOWTASKSCOMMAND_H
