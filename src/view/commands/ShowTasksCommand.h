//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_SHOWTASKSCOMMAND_H
#define SIMPLETASKMANAGER_SHOWTASKSCOMMAND_H

#include "CommandInterface.h"
#include "Task.pb.h"

class ShowTasksCommand : public CommandInterface {
public:
    void Execute() override;
};


#endif //SIMPLETASKMANAGER_SHOWTASKSCOMMAND_H
