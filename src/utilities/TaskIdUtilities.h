//
// Created by Maksym Kharchenko on 14.12.2021.
//

#ifndef SIMPLETASKMANAGER_TASKIDUTILITIES_H
#define SIMPLETASKMANAGER_TASKIDUTILITIES_H

#include "Task.pb.h"

bool operator<(const TaskId& task_id1, const TaskId& task_id2) const {
    return task_id1.id() < task_id2.id();
}

bool operator==(const TaskId& task_id1, const TaskId& task_id2) const {
    return task_id1.id() == task_id2.id();
}

#endif //SIMPLETASKMANAGER_TASKIDUTILITIES_H
