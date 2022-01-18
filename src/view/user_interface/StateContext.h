//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_STATECONTEXT_H
#define SIMPLETASKMANAGER_STATECONTEXT_H

#include "Task.pb.h"
#include "commands/Command.h"
#include "utilities/TaskBuilder.h"

#include <memory>
#include <string>
#include <optional>
#include <ctime>

class StateContext {
public:
    StateContext();
public:
    void AddTaskTitle(const std::string& title);
    void AddTaskPriority(Task::Priority priority);
    void AddTaskDueTime(const google::protobuf::Timestamp& due_time);

    void SetTaskLabel(const std::string& task_label);
    std::string GetTaskLabel() const;

    void SetTaskBuilder(const TaskBuilder& task_builder);
    TaskBuilder GetTaskBuilder() const;

    void SetTaskId(const TaskId& task_id);
    virtual std::optional<TaskId> GetTaskId() const;

    void SetFileName(const std::string& file_name);
    std::string GetFileName() const;

    void SetCommand(std::unique_ptr<Command> command);
    std::shared_ptr<Command> GetCommand() const;

    void SetTasksToShow(const CommandResult::TasksToShow& tasks);
    CommandResult::TasksToShow GetTasksToShow() const;
public:
    virtual ~StateContext() = default;
private:
    TaskBuilder task_;
    std::optional<TaskId> task_id_;
    std::string task_label_;

    CommandResult::TasksToShow tasks_to_show_;

    std::string file_name_;

    std::shared_ptr<Command> command_;
};


#endif //SIMPLETASKMANAGER_STATECONTEXT_H
