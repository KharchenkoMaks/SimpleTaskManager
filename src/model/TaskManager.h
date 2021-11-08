//
// Created by Maksym Kharchenko on 08.11.2021.
//

#ifndef SIMPLETASKMANAGER_TASKMANAGER_H
#define SIMPLETASKMANAGER_TASKMANAGER_H

#include "Task.h"

#include <map>
#include <vector>
#include <utility>

class TaskManager {
public:
    int Create(Task t);
    void Edit(int id, Task t);
    void Delete(int id);
    std::vector<std::pair<int, Task>> Show();
    TaskManager();
private:
    int next_id_;
    std::map<int, Task> tasks_;
};


#endif //SIMPLETASKMANAGER_TASKMANAGER_H
