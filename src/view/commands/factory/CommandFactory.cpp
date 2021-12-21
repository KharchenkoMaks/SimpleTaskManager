//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "CommandFactory.h"

#include "commands/AddSubTaskCommand.h"
#include "commands/AddTaskCommand.h"
#include "commands/EditTaskCommand.h"
#include "commands/CompleteTaskCommand.h"
#include "commands/DeleteTaskCommand.h"
#include "commands/SetLabelCommand.h"
#include "commands/ShowTasksCommand.h"
#include "commands/SaveCommand.h"
#include "commands/LoadCommand.h"

std::unique_ptr<CommandInterface> CommandFactory::CreateAddTaskCommand(const StateContext& context) {
    std::optional<Task> task_to_add = context.GetTask();
    if (task_to_add.has_value())
        return std::make_unique<AddTaskCommand>(controller_, task_to_add.value());

    return nullptr;
}

std::unique_ptr<CommandInterface> CommandFactory::CreateAddSubTaskCommand(const StateContext& context) {
    std::optional<Task> task_to_add = context.GetTask();
    std::optional<TaskId> parent_task_id = context.GetTaskId();
    if (task_to_add.has_value() && parent_task_id.has_value())
        return std::make_unique<AddSubTaskCommand>(controller_, task_to_add.value(), parent_task_id.value());

    return nullptr;
}

std::unique_ptr<CommandInterface> CommandFactory::CreateEditCommand(const StateContext& context) {
    std::optional<Task> edited_task = context.GetTask();
    std::optional<TaskId> edited_task_id = context.GetTaskId();
    if (edited_task.has_value() && edited_task_id.has_value())
        return std::make_unique<EditTaskCommand>(controller_, edited_task.value(), edited_task_id.value());

    return nullptr;
}

std::unique_ptr<CommandInterface> CommandFactory::CreateCompleteCommand(const StateContext& context) {
    std::optional<TaskId> task_id = context.GetTaskId();
    if (task_id.has_value())
        return std::make_unique<CompleteTaskCommand>(controller_, task_id.value());

    return nullptr;
}

std::unique_ptr<CommandInterface> CommandFactory::CreateDeleteCommand(const StateContext& context) {
    std::optional<TaskId> task_id = context.GetTaskId();
    if (task_id.has_value())
        return std::make_unique<DeleteTaskCommand>(controller_, task_id.value());

    return nullptr;
}

std::unique_ptr<CommandInterface> CommandFactory::CreateSetLabelCommand(const StateContext& context) {
    std::optional<TaskId> task_id = context.GetTaskId();
    std::string task_label = context.GetTaskLabel();
    if (task_id.has_value() && !task_label.empty())
        return std::make_unique<SetLabelCommand>(controller_, task_id.value(), task_label);

    return nullptr;
}

std::unique_ptr<CommandInterface> CommandFactory::CreateShowCommand(const StateContext& context) {
    return std::make_unique<ShowTasksCommand>(controller_);
}

std::unique_ptr<CommandInterface> CommandFactory::CreateSaveCommand(const StateContext& context) {
    std::string file_name = context.GetFileName();
    if (!file_name.empty())
        return std::make_unique<SaveCommand>(controller_, file_name);

    return nullptr;
}

std::unique_ptr<CommandInterface> CommandFactory::CreateLoadCommand(const StateContext& context) {
    std::string file_name = context.GetFileName();
    if (!file_name.empty())
        return std::make_unique<LoadCommand>(controller_, file_name);

    return nullptr;
}

CommandFactory::CommandFactory(std::unique_ptr<Controller> controller) : controller_(std::move(controller)) {

}
