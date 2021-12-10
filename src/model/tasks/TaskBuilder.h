//
// Created by Maksym Kharchenko on 10.12.2021.
//

#ifndef SIMPLETASKMANAGER_TASKBUILDER_H
#define SIMPLETASKMANAGER_TASKBUILDER_H

#include "Task.h"
#include "DueTime.h"

#include <optional>
#include <string>

class TaskBuilder {
public:
    TaskBuilder();
public:
    TaskBuilder& SetTitle(const std::string& title);
    TaskBuilder& SetPriority(Task::Priority priority);
    TaskBuilder& SetDueTime(const DueTime& due_time);
    TaskBuilder& SetCompletionState(bool completed);
    TaskBuilder& SetLabel(const std::string& label);
public:
    std::optional<Task> BuildTask();

    void ResetTask();
public:
    TaskBuilder& operator= (const Task& task);
private:
    std::optional<std::string> title_;
    Task::Priority priority_;
    std::optional<DueTime> due_time_;
    bool completed_;
    std::string label_;
};


#endif //SIMPLETASKMANAGER_TASKBUILDER_H
