//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_STATECONTEXT_H
#define SIMPLETASKMANAGER_STATECONTEXT_H

#include "Task.pb.h"
#include "commands/CommandInterface.h"
#include "utilities/TaskBuilder.h"

#include <memory>
#include <string>
#include <optional>
#include <ctime>

class StateContext {
public:
    StateContext();
public:
    // Returns false if title isn't added
    bool AddTaskTitle(const std::string& title);
    // Returns false if priority isn't added
    bool AddTaskPriority(Task::Priority priority);
    // Returns false if due time isn't added
    bool AddTaskDueTime(const google::protobuf::Timestamp& due_time);
    void AddTaskLabel(const std::string& task_label);
    void SetTaskLabel(const std::string& label);
    std::string GetTaskLabel() const;

    void SetTaskBuilder(const TaskBuilder& task_builder);
    TaskBuilder GetTaskBuilder() const;

    void SetTaskId(const TaskId& task_id);
    virtual std::optional<TaskId> GetTaskId() const;

    void SetFileName(const std::string& file_name);
    std::string GetFileName() const;

    void SetCommand(std::unique_ptr<CommandInterface> command);
    std::shared_ptr<CommandInterface> GetCommand() const;
public:
    virtual ~StateContext() = default;
private:
    TaskBuilder task_;
    std::optional<TaskId> task_id_;

    std::string file_name_;

    std::shared_ptr<CommandInterface> command_;
};


#endif //SIMPLETASKMANAGER_STATECONTEXT_H
