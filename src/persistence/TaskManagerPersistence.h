//
// Created by Maksym Kharchenko on 15.12.2021.
//

#ifndef SIMPLETASKMANAGER_TASKMANAGERPERSISTENCE_H
#define SIMPLETASKMANAGER_TASKMANAGERPERSISTENCE_H

#include "Task.pb.h"

#include <vector>
#include <utility>

class TaskManagerPersistence {
public:
    enum class SaveLoadStatus {
        SUCCESS,
        FILE_WAS_NOT_OPENED,
        INVALID_FILE_STRUCTURE
    };
public:
    struct TaskManagerParameters {
        TaskManagerParameters() = default;
        TaskManagerParameters(const TaskId& last_id,
                              const std::vector<TaskTransfer>& tasks);
        TaskId last_id_;
        std::vector<TaskTransfer> tasks_;
    };
public:
    std::pair<SaveLoadStatus, TaskManagerParameters> LoadFromFile(const std::string& file_name);
    SaveLoadStatus SaveToFile(const std::string& file_name, const TaskManagerParameters& parameters_to_save);
};


#endif //SIMPLETASKMANAGER_TASKMANAGERPERSISTENCE_H
