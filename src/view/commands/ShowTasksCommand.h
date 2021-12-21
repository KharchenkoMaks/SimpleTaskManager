//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_SHOWTASKSCOMMAND_H
#define SIMPLETASKMANAGER_SHOWTASKSCOMMAND_H

#include "CommandInterface.h"
#include "Task.pb.h"
#include "controller/Controller.h"

#include <memory>

class ShowTasksCommand : public CommandInterface {
public:
    explicit ShowTasksCommand(const std::shared_ptr<Controller>& controller);
public:
    void Execute() override;
private:
    std::shared_ptr<Controller> controller_;
};


#endif //SIMPLETASKMANAGER_SHOWTASKSCOMMAND_H
