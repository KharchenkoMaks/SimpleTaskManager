//
// Created by Maksym Kharchenko on 19.11.2021.
//

#ifndef SIMPLETASKMANAGER_SUBTASK_H
#define SIMPLETASKMANAGER_SUBTASK_H

#include "tasks/Task.h"
#include "DueTime.h"

class SubTask {
public:
    static SubTask Create(const std::string& title,
                       Task::Priority priority,
                       DueTime due_to,
                       const TaskId& parent,
                       bool completed = false,
                       const std::string& label = std::string(""));
    static SubTask Create(const Task& task, const TaskId& parent);
public:
    Task GetTaskParameters() const;
    TaskId GetParentTaskId() const;
public:
    bool operator== (const SubTask& task) const;
private:
    SubTask(const std::string& title,
         Task::Priority priority,
         DueTime due_to,
         const TaskId& parent,
         bool completed = false,
         const std::string& label = std::string(""));
private:
    TaskId parent_;
    Task task_;
};


#endif //SIMPLETASKMANAGER_SUBTASK_H
