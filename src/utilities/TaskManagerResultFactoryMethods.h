//
// Created by Maksym Kharchenko on 26.01.2022.
//

#ifndef SIMPLETASKMANAGER_TASKMANAGERRESULTFACTORYMETHODS_H
#define SIMPLETASKMANAGER_TASKMANAGERRESULTFACTORYMETHODS_H

#include "TaskActionResult.h"
#include "Responses.pb.h"

TaskActionResult CreateTaskActionResult(const TaskManagerServiceResult& request_result);

TaskManagerServiceResult CreateTaskManagerServiceResult(const TaskActionResult& action_result);

#endif //SIMPLETASKMANAGER_TASKMANAGERRESULTFACTORYMETHODS_H
