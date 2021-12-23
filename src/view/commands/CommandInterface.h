//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_COMMANDINTERFACE_H
#define SIMPLETASKMANAGER_COMMANDINTERFACE_H

#include "controller/Controller.h"

class CommandInterface {
public:
    virtual void Execute(const std::shared_ptr<Controller>& controller) = 0;
public:
    virtual ~CommandInterface() = default;
};

#endif //SIMPLETASKMANAGER_COMMANDINTERFACE_H
