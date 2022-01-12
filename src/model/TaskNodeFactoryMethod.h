//
// Created by Maksym Kharchenko on 12.01.2022.
//

#ifndef SIMPLETASKMANAGER_TASKNODEFACTORYMETHOD_H
#define SIMPLETASKMANAGER_TASKNODEFACTORYMETHOD_H

#include "Task.pb.h"
#include "TaskNode.pb.h"

namespace model {

TaskNode Create(Task task);

TaskNode Create (Task task, TaskId parent_id);

}


#endif //SIMPLETASKMANAGER_TASKNODEFACTORYMETHOD_H
