//
// Created by Maksym Kharchenko on 23.12.2021.
//

#ifndef SIMPLETASKMANAGER_USERINTERFACE_H
#define SIMPLETASKMANAGER_USERINTERFACE_H

#include "user_interface/console_io/ConsolePrinter.h"
#include "user_interface/console_io/ConsoleReader.h"
#include "states/factory/StatesFactory.h"
#include "commands/CommandInterface.h"
#include "model/controller/ControllerRequestResult.h"

#include <memory>
#include <string>

class UserInterface {
public:
    UserInterface(const std::shared_ptr<StatesFactory>& states_factory);
public:
    virtual std::shared_ptr<CommandInterface> AskUserForAction();
public:
    virtual void PrintAddedTaskId(const TaskId& task_id);
    virtual void PrintRequestResult(ControllerRequestResult action_result);
    virtual void ShowTasks(const std::vector<TaskTransfer>& tasks);
public:
    virtual ~UserInterface() = default;
private:
    std::shared_ptr<StatesFactory> states_factory_;
};


#endif //SIMPLETASKMANAGER_USERINTERFACE_H
