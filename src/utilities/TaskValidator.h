//
// Created by Maksym Kharchenko on 29.11.2021.
//

#ifndef SIMPLETASKMANAGER_TASKVALIDATOR_H
#define SIMPLETASKMANAGER_TASKVALIDATOR_H

#include "Task.pb.h"

#include <ctime>
#include <string>

class TaskValidator {
public:
    virtual bool ValidateTask(const Task& task);
    virtual bool ValidateTaskId(const TaskId& task_id);
public:
    virtual ~TaskValidator() = default;
private:
    bool ValidateTitle(const std::string& title);
    bool ValidateDueDate(google::protobuf::Timestamp due_date);
};


#endif //SIMPLETASKMANAGER_TASKVALIDATOR_H
