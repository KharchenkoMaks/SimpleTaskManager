//
// Created by Maksym Kharchenko on 12.11.2021.
//

#ifndef SIMPLETASKMANAGER_IDGENERATOR_H
#define SIMPLETASKMANAGER_IDGENERATOR_H

#include "TaskId.h"

class IdGenerator{
public:
    IdGenerator();
    explicit IdGenerator(int last_id);
    TaskId CreateNewTaskId();
private:
    int last_id_;
};


#endif //SIMPLETASKMANAGER_IDGENERATOR_H
