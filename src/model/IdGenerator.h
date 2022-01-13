//
// Created by Maksym Kharchenko on 12.11.2021.
//

#ifndef SIMPLETASKMANAGER_IDGENERATOR_H
#define SIMPLETASKMANAGER_IDGENERATOR_H

#include "Task.pb.h"

class IdGenerator{
public:
    IdGenerator();
public:
    virtual TaskId CreateNewTaskId();
public:
    virtual bool SetLastTaskId(const TaskId& task_id);
public:
    virtual ~IdGenerator();
private:
    int last_id_;
};


#endif //SIMPLETASKMANAGER_IDGENERATOR_H
