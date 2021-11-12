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
    TaskId Create(Task t);
    void Edit(TaskId id, Task t);
    void Delete(TaskId id);
    void Complete(TaskId id);
    std::vector<std::pair<TaskId, Task>> Show();
    TaskManager();
private:
    std::map<TaskId, Task> tasks_;
    IdGenerator generator_;
};


#endif //SIMPLETASKMANAGER_TASKMANAGER_H
