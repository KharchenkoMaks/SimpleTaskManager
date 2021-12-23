//
// Created by Maksym Kharchenko on 23.12.2021.
//

#ifndef SIMPLETASKMANAGER_TASKCOMPARATORS_H
#define SIMPLETASKMANAGER_TASKCOMPARATORS_H

#include "Task.pb.h"

#include <google/protobuf/util/time_util.h>

bool operator<(const TaskId& task_id1, const TaskId& task_id2);

bool operator==(const TaskId& task_id1, const TaskId& task_id2);

bool operator==(const TaskTransfer& task1, const TaskTransfer& task2);

bool operator==(const Task& task1, const Task& task2);

#endif //SIMPLETASKMANAGER_TASKCOMPARATORS_H
