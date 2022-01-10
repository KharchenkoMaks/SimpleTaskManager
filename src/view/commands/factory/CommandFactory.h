//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_COMMANDFACTORY_H
#define SIMPLETASKMANAGER_COMMANDFACTORY_H

#include "view/commands/CommandInterface.h"
#include "controller/Controller.h"
#include "user_interface/StateContext.h"

#include <memory>
#include <optional>

class CommandFactory {
public:
    virtual std::unique_ptr<CommandInterface> CreateAddTaskCommand(const StateContext& context);
    virtual std::unique_ptr<CommandInterface> CreateAddSubTaskCommand(const StateContext& context);
    virtual std::unique_ptr<CommandInterface> CreateEditCommand(const StateContext& context);
    virtual std::unique_ptr<CommandInterface> CreateCompleteCommand(const StateContext& context, bool force_complete_subtasks);
    virtual std::unique_ptr<CommandInterface> CreateDeleteCommand(const StateContext& context, bool force_delete_subtasks);
    virtual std::unique_ptr<CommandInterface> CreateSetLabelCommand(const StateContext& context);
    virtual std::unique_ptr<CommandInterface> CreateShowCommand(const StateContext& context);
    virtual std::unique_ptr<CommandInterface> CreateSaveCommand(const StateContext& context);
    virtual std::unique_ptr<CommandInterface> CreateLoadCommand(const StateContext& context);
public:
    virtual ~CommandFactory() = default;
};


#endif //SIMPLETASKMANAGER_COMMANDFACTORY_H
