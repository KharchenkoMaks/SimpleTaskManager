//
// Created by Maksym Kharchenko on 14.12.2021.
//

#ifndef SIMPLETASKMANAGER_MAINTASK_H
#define SIMPLETASKMANAGER_MAINTASK_H

#include "Task.pb.h"
#include "utilities/TaskIdUtilities.h"

#include <map>
#include <utility>

class MainTask {
public:
    static MainTask Create(const Task& task);
public:
    void AddSubTask(const TaskId& task_id, const Task& subtask);
public:
    bool ContainsSubTask(const TaskId& subtask_id);
private:
    explicit MainTask(const Task& task);
public:
    Task task_;
    std::map<TaskId, Task> subtasks_;
};


#endif //SIMPLETASKMANAGER_MAINTASK_H
