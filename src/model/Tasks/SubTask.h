//
// Created by Maksym Kharchenko on 19.11.2021.
//

#ifndef SIMPLETASKMANAGER_SUBTASK_H
#define SIMPLETASKMANAGER_SUBTASK_H

#include "Tasks/Task.h"

class SubTask : public Task {
public:
    static SubTask Create(const std::string& title,
                       Priority priority,
                       time_t due_to,
                       const TaskId& parent,
                       bool completed = false,
                       const std::string& label = std::string(""));
public:
    TaskId GetParentTaskId() override;
private:
    SubTask(const std::string& title,
         Priority priority,
         time_t due_to,
         const TaskId& parent,
         bool completed = false,
         const std::string& label = std::string(""));
private:
    TaskId parent_;
};


#endif //SIMPLETASKMANAGER_SUBTASK_H
