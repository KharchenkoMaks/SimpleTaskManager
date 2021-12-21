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
    std::pair<SaveLoadStatus, std::vector<TaskTransfer>> LoadFromFile(const std::string& file_name);

    SaveLoadStatus SaveToFile(const std::string &file_name, const std::vector<TaskTransfer>& tasks_to_save);
};

}

#endif //SIMPLETASKMANAGER_TASKSPERSISTENCE_H
