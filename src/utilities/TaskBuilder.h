//
// Created by Maksym Kharchenko on 22.12.2021.
//

#ifndef SIMPLETASKMANAGER_TASKBUILDER_H
#define SIMPLETASKMANAGER_TASKBUILDER_H

#include "Task.pb.h"

#include <string>
#include <optional>

class TaskBuilder {
public:
    static TaskBuilder Create();
public:
    TaskBuilder& SetTitle(const std::string& title);
    TaskBuilder& SetPriority(Task::Priority priority);
    TaskBuilder& SetDueDate(const google::protobuf::Timestamp& due_date);
    TaskBuilder& SetCompletion(bool is_completed);
    TaskBuilder& SetLabel(const std::string& label);

    TaskBuilder& Merge(const Task& task);
public:
    Task BuildTask() const;
private:
    TaskBuilder() = default;
private:
    std::optional<std::string> title_;
    std::optional<Task::Priority> priority_;
    std::optional<google::protobuf::Timestamp> due_date_;
    std::optional<bool> is_completed_;
    std::optional<std::string> label_;
};


#endif //SIMPLETASKMANAGER_TASKBUILDER_H