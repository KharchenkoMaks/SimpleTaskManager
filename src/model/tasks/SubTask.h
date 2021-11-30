//
// Created by Maksym Kharchenko on 19.11.2021.
//

#ifndef SIMPLETASKMANAGER_SUBTASK_H
#define SIMPLETASKMANAGER_SUBTASK_H

#include "tasks/Task.h"
#include "DueTime.h"

class SubTask : public Task {
public:
    static SubTask Create(const std::string& title,
                       Priority priority,
                       DueTime due_to,
                       const TaskId& parent,
                       bool completed = false,
                       const std::string& label = std::string(""));
public:
    TaskId GetParentTaskId() override;
public:
    bool operator== (const SubTask& task) const;
private:
    SubTask(const std::string& title,
         Priority priority,
         DueTime due_to,
         const TaskId& parent,
         bool completed = false,
         const std::string& label = std::string(""));
private:
    TaskId parent_;
};


#endif //SIMPLETASKMANAGER_SUBTASK_H
