//
// Created by Maksym Kharchenko on 12.01.2022.
//

#ifndef SIMPLETASKMANAGER_PERSISTENCE_H
#define SIMPLETASKMANAGER_PERSISTENCE_H

#include "Task.pb.h"
#include "utilities/SaveLoadStatus.h"

namespace persistence {

class Persistence {
public:
    virtual std::pair<SaveLoadStatus, std::vector<TaskTransfer>> Load() = 0;
    virtual SaveLoadStatus Save(const std::vector<TaskTransfer> &tasks) = 0;

public:
    virtual ~Persistence() = default;
};

}
#endif //SIMPLETASKMANAGER_PERSISTENCE_H
