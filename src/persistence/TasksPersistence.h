//
// Created by Maksym Kharchenko on 15.12.2021.
//

#ifndef SIMPLETASKMANAGER_TASKSPERSISTENCE_H
#define SIMPLETASKMANAGER_TASKSPERSISTENCE_H

#include "Task.pb.h"
#include "utilities/SaveLoadStatus.h"

#include <vector>
#include <utility>

namespace persistence {

class TasksPersistence {
public:
    struct TaskManagerParameters {
        TaskManagerParameters() = default;

        TaskManagerParameters(const TaskId &last_id,
                              const std::vector<TaskTransfer> &tasks);

        TaskId last_id_;
        std::vector<TaskTransfer> tasks_;
    };

public:
    std::pair<SaveLoadStatus, TaskManagerParameters> LoadFromFile(const std::string &file_name);

    SaveLoadStatus SaveToFile(const std::string &file_name, const TaskManagerParameters &parameters_to_save);
};

}

#endif //SIMPLETASKMANAGER_TASKSPERSISTENCE_H
