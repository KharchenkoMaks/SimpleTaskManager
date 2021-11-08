//
// Created by Maksym Kharchenko on 08.11.2021.
//

#ifndef SIMPLETASKMANAGER_TASKMANAGER_H
#define SIMPLETASKMANAGER_TASKMANAGER_H

#include "Task.h"

#include <map>

class TaskManager {
public:
    int Create(Task t);
    void Edit(Task t);
    void Delete(Task t);
    std::vector<std::pair<int, Task>> Show();
private:
    std::map<int, Task> tasks_;
};


#endif //SIMPLETASKMANAGER_TASKMANAGER_H
