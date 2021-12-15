//
// Created by Maksym Kharchenko on 15.12.2021.
//

#ifndef SIMPLETASKMANAGER_TASKMANAGERPERSISTENCE_H
#define SIMPLETASKMANAGER_TASKMANAGERPERSISTENCE_H

#include "Task.pb.h"

#include <vector>

class TaskManagerPersistence {
public:
    struct TaskManagerParameters {
        TaskId last_id_;
        std::vector<TaskTransfer> tasks_;
    };
public:
    TaskManagerParameters LoadFromFile(const std::string& file_name);
    bool SaveToFile(const std::string& file_name, const TaskManagerParameters& parameters_to_save);
};


#endif //SIMPLETASKMANAGER_TASKMANAGERPERSISTENCE_H
