//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_COMMAND_H
#define SIMPLETASKMANAGER_COMMAND_H

#include "controller/Controller.h"
#include "CommandResult.h"

class Command {
public:
    virtual CommandResult Execute(const std::shared_ptr<Controller>& controller) = 0;
public:
    virtual ~Command() = default;
};

#endif //SIMPLETASKMANAGER_COMMAND_H
