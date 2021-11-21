//
// Created by Maksym Kharchenko on 08.11.2021.
//

#ifndef SIMPLETASKMANAGER_TASK_H
#define SIMPLETASKMANAGER_TASK_H

#include "TaskId.h"

#include <string>
#include <ctime>

class Task {
public:
    enum class Priority {
        HIGH,
        MEDIUM,
        LOW,
        NONE
    };
public:
    static Task Create(const std::string& title,
                       Priority priority,
                       time_t due_to,
                       bool completed = false,
                       const std::string& label = std::string(""));
public:
    // throws std::runtime_eror if task is already completed
    std::string to_string();

    std::string GetTitle();
    Task::Priority GetPriority();
    time_t GetDueTime();
    bool IsCompleted();
    std::string GetLabel();

    virtual TaskId GetParentTaskId();
public:
    bool operator== (const Task& task) const;
protected:
    Task(const std::string& title,
         Priority priority,
         time_t due_to,
         bool completed = false,
         const std::string& label = std::string(""));
private:
    std::string title_;
    Priority priority_;
    time_t due_to_;
    bool completed_;
    std::string label_;
};


#endif //SIMPLETASKMANAGER_TASK_H
