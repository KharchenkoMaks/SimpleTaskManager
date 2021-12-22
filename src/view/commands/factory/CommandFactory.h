//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_COMMANDFACTORY_H
#define SIMPLETASKMANAGER_COMMANDFACTORY_H

#include "view/commands/CommandInterface.h"
#include "controller/Controller.h"
#include "StateContext.h"
#include "console_io/ConsolePrinter.h"

#include <memory>
#include <optional>

class CommandFactory {
public:
    std::unique_ptr<CommandInterface> CreateAddTaskCommand(const StateContext& context);
    std::unique_ptr<CommandInterface> CreateAddSubTaskCommand(const StateContext& context);
    std::unique_ptr<CommandInterface> CreateEditCommand(const StateContext& context);
    std::unique_ptr<CommandInterface> CreateCompleteCommand(const StateContext& context);
    std::unique_ptr<CommandInterface> CreateDeleteCommand(const StateContext& context);
    std::unique_ptr<CommandInterface> CreateSetLabelCommand(const StateContext& context);
    std::unique_ptr<CommandInterface> CreateShowCommand(const StateContext& context);
    std::unique_ptr<CommandInterface> CreateSaveCommand(const StateContext& context);
    std::unique_ptr<CommandInterface> CreateLoadCommand(const StateContext& context);
};


#endif //SIMPLETASKMANAGER_COMMANDFACTORY_H
