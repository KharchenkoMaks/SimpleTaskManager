//
// Created by Maksym Kharchenko on 29.11.2021.
//

#ifndef SIMPLETASKMANAGER_TASKVALIDATOR_H
#define SIMPLETASKMANAGER_TASKVALIDATOR_H

#include "tasks/Task.h"
#include "TaskId.h"

class TaskValidator {
public:
    bool ValidateTask(const Task& task);
    bool ValidateTaskId(const TaskId& task_id);
};


#endif //SIMPLETASKMANAGER_TASKVALIDATOR_H
