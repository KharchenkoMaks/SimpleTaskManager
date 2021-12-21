//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_SHOWTASKSCOMMAND_H
#define SIMPLETASKMANAGER_SHOWTASKSCOMMAND_H

#include "CommandInterface.h"
#include "Task.pb.h"
#include "controller/Controller.h"
#include "console_io/ConsolePrinter.h"

#include <memory>

class ShowTasksCommand : public CommandInterface {
public:
    ShowTasksCommand(const std::shared_ptr<Controller>& controller,
                     const std::shared_ptr<ConsolePrinter>& printer);
public:
    void Execute() override;
private:
    std::shared_ptr<Controller> controller_;

    std::shared_ptr<ConsolePrinter> printer_;
};


#endif //SIMPLETASKMANAGER_SHOWTASKSCOMMAND_H
