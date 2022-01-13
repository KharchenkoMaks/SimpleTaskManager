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

std::unique_ptr<Command> CommandFactory::CreateAddTaskCommand(const StateContext& context) {
    std::optional<Task> task_to_add = context.GetTaskBuilder().BuildTask();
    if (task_to_add.has_value())
        return std::make_unique<AddTaskCommand>(task_to_add.value());

    return nullptr;
}

std::unique_ptr<Command> CommandFactory::CreateAddSubTaskCommand(const StateContext& context) {
    std::optional<Task> task_to_add = context.GetTaskBuilder().BuildTask();
    std::optional<TaskId> parent_task_id = context.GetTaskId();
    if (task_to_add.has_value() && parent_task_id.has_value())
        return std::make_unique<AddSubTaskCommand>(task_to_add.value(), parent_task_id.value());

    return nullptr;
}

std::unique_ptr<Command> CommandFactory::CreateEditCommand(const StateContext& context) {
    TaskBuilder edited_task = context.GetTaskBuilder();
    std::optional<TaskId> edited_task_id = context.GetTaskId();
    if (edited_task_id.has_value())
        return std::make_unique<EditTaskCommand>(edited_task, edited_task_id.value());

    return nullptr;
}

std::unique_ptr<Command> CommandFactory::CreateCompleteCommand(const StateContext& context, bool force_complete_subtasks) {
    std::optional<TaskId> task_id = context.GetTaskId();
    if (task_id.has_value())
        return std::make_unique<CompleteTaskCommand>(task_id.value(), force_complete_subtasks);

    return nullptr;
}

std::unique_ptr<Command> CommandFactory::CreateDeleteCommand(const StateContext& context, bool force_delete_subtasks) {
    std::optional<TaskId> task_id = context.GetTaskId();
    if (task_id.has_value())
        return std::make_unique<DeleteTaskCommand>(task_id.value(), force_delete_subtasks);

    return nullptr;
}

std::unique_ptr<Command> CommandFactory::CreateSetLabelCommand(const StateContext& context) {
    std::optional<TaskId> task_id = context.GetTaskId();
    std::string task_label = context.GetTaskLabel();
    if (task_id.has_value() && !task_label.empty())
        return std::make_unique<SetLabelCommand>(task_id.value(), task_label);

    return nullptr;
}

std::unique_ptr<Command> CommandFactory::CreateShowCommand(const StateContext& context) {
    return std::make_unique<ShowTasksCommand>();
}

std::unique_ptr<Command> CommandFactory::CreateSaveCommand(const StateContext& context) {
    std::string file_name = context.GetFileName();
    if (!file_name.empty())
        return std::make_unique<SaveCommand>(file_name);

    return nullptr;
}

std::unique_ptr<Command> CommandFactory::CreateLoadCommand(const StateContext& context) {
    std::string file_name = context.GetFileName();
    if (!file_name.empty())
        return std::make_unique<LoadCommand>(file_name);

    return nullptr;
}
