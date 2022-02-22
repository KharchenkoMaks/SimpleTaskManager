//
// Created by Maksym Kharchenko on 21.12.2021.
//

#ifndef SIMPLETASKMANAGER_COMMANDFACTORY_H
#define SIMPLETASKMANAGER_COMMANDFACTORY_H

#include "view/commands/Command.h"
#include "user_interface/StateContext.h"

#include <memory>
#include <optional>

class CommandFactory {
public:
    /**
     * @param context with filled \b TaskBuilder
     * @return \b std::unique_ptr on \b AddTaskCommand
     */
    virtual std::unique_ptr<Command> CreateAddTaskCommand(const StateContext& context);
    /**
     * @param context with filled \b TaskBuilder and \b TaskId
     * @return \b std::unique_ptr on \b AddSubTaskCommand
     * @warning If \b TaskId is not filled in \b context method will return \b nullptr
     */
    virtual std::unique_ptr<Command> CreateAddSubTaskCommand(const StateContext& context);
    /**
     * @param context with filled \b TaskBuilder and \b TaskId
     * @return \b std::unique_ptr on \b EditTaskCommand
     * @warning If \b TaskId is not filled in \b context method will return \b nullptr
     */
    virtual std::unique_ptr<Command> CreateEditCommand(const StateContext& context);
    /**
     * @param context with filled \b TaskId
     * @param force_complete_subtasks if force completing subtasks is needed
     * @return \b std::unique_ptr on \b CompleteTaskCommand
     * @warning If \b TaskId is not filled in \b context method will return \b nullptr
     */
    virtual std::unique_ptr<Command> CreateCompleteCommand(const StateContext& context, bool force_complete_subtasks);
    /**
     * @param context with filled \b TaskId
     * @param force_delete_subtasks if force deleting subtasks is needed
     * @return \b std::unique_ptr on \b DeleteTaskCommand
     * @warning If \b TaskId is not filled in \b context method will return \b nullptr
     */
    virtual std::unique_ptr<Command> CreateDeleteCommand(const StateContext& context, bool force_delete_subtasks);
    /**
     * @param context with filled \b TaskId and \b TaskLabel
     * @return \b std::unique_ptr on \b SetLabelCommand
     * @warning If \b TaskId is not filled in \b context method will return \b nullptr
     */
    virtual std::unique_ptr<Command> CreateSetLabelCommand(const StateContext& context);
    /**
     * @param context context with filled \b TaskId and \b TaskLabel
     * @return \b std::unique_ptr on \b RemoveLabelCommand
     * @warning If \b TaskId is not filled in \b context method will return \b nullptr
     */
    virtual std::unique_ptr<Command> CreateRemoveLabelCommand(const StateContext& context);
    /**
     * @param context context with filled \b TaskLabel
     * @return \b std::unique_ptr on \b ShowCommand
     * @attention Empty TaskLabel is legit
     */
    virtual std::unique_ptr<Command> CreateShowCommand(const StateContext& context);
    /**
     * @param context with filled \b FileName
     * @return std::unique_ptr on \b SaveCommand
     * @warning If \b FileName is empty method will return nullptr
     */
    virtual std::unique_ptr<Command> CreateSaveCommand(const StateContext& context);
    /**
     * @param context with filled \b FileName
     * @return std::unique_ptr on \b LoadCommand
     * @warning If \b FileName is empty method will return nullptr
     */
    virtual std::unique_ptr<Command> CreateLoadCommand(const StateContext& context);
public:
    virtual ~CommandFactory() = default;
};


#endif //SIMPLETASKMANAGER_COMMANDFACTORY_H
