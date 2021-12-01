//
// Created by Maksym Kharchenko on 08.11.2021.
//

#ifndef SIMPLETASKMANAGER_TASK_H
#define SIMPLETASKMANAGER_TASK_H

#include "TaskId.h"
#include "DueTime.h"

#include <string>
#include <ctime>
#include <optional>

class Task {
public:
    enum class Priority {
        HIGH,
        MEDIUM,
        LOW,
        NONE
    };

    static std::string PriorityToString(Priority priority);
    static std::optional<Priority> GetTaskPriority(const std::string& priority);
public:
    static Task Create(const std::string& title,
                       Priority priority,
                       DueTime due_to,
                       bool completed = false,
                       const std::string& label = std::string(""));
public:
    // throws std::runtime_eror if task is already completed
    std::string to_string() const;

    std::string GetTitle() const;
    Task::Priority GetPriority() const;
    DueTime GetDueTime() const;
    bool IsCompleted() const;
    std::string GetLabel() const;

    virtual TaskId GetParentTaskId();
public:
    virtual bool operator== (const Task& task) const;
protected:
    Task(const std::string& title,
         Priority priority,
         DueTime due_to,
         bool completed = false,
         const std::string& label = std::string(""));
protected:
    std::string title_;
    Priority priority_;
    DueTime due_to_;
    bool completed_;
    std::string label_;
};


#endif //SIMPLETASKMANAGER_TASK_H
