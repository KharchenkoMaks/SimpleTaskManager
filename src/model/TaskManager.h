//
// Created by Maksym Kharchenko on 08.11.2021.
//

#ifndef SIMPLETASKMANAGER_TASKMANAGER_H
#define SIMPLETASKMANAGER_TASKMANAGER_H

#include "Task.h"
#include "TaskId.h"
#include "IdGenerator.h"

#include <map>
#include <vector>
#include <utility>

class TaskManager {
public:
    TaskId Create(const Task& t);
    void Edit(const TaskId& id, const Task& t);
    void Delete(const TaskId& id);
    void Complete(const TaskId& id);
    std::vector<std::pair<TaskId, Task>> Show();
    TaskManager();
private:
    std::map<TaskId, Task> tasks_;
    IdGenerator generator_;
};


#endif //SIMPLETASKMANAGER_TASKMANAGER_H
