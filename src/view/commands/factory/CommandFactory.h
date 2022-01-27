//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_COMMANDFACTORY_H
#define SIMPLETASKMANAGER_COMMANDFACTORY_H

#include "view/commands/Command.h"
#include "controller/ModelController.h"
#include "user_interface/StateContext.h"

#include <memory>
#include <optional>

class CommandFactory {
public:
    virtual std::unique_ptr<Command> CreateAddTaskCommand(const StateContext& context);
    virtual std::unique_ptr<Command> CreateAddSubTaskCommand(const StateContext& context);
    virtual std::unique_ptr<Command> CreateEditCommand(const StateContext& context);
    virtual std::unique_ptr<Command> CreateCompleteCommand(const StateContext& context, bool force_complete_subtasks);
    virtual std::unique_ptr<Command> CreateDeleteCommand(const StateContext& context, bool force_delete_subtasks);
    virtual std::unique_ptr<Command> CreateSetLabelCommand(const StateContext& context);
    virtual std::unique_ptr<Command> CreateRemoveLabelCommand(const StateContext& context);
    virtual std::unique_ptr<Command> CreateShowCommand(const StateContext& context);
    virtual std::unique_ptr<Command> CreateSaveCommand(const StateContext& context);
    virtual std::unique_ptr<Command> CreateLoadCommand(const StateContext& context);
public:
    virtual ~CommandFactory() = default;
};


#endif //SIMPLETASKMANAGER_COMMANDFACTORY_H
