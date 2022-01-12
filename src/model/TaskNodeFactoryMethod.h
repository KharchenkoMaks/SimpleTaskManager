//
// Created by Maksym Kharchenko on 12.01.2022.
//

#ifndef SIMPLETASKMANAGER_TASKNODEFACTORYMETHOD_H
#define SIMPLETASKMANAGER_TASKNODEFACTORYMETHOD_H

#include "Task.pb.h"
#include "TaskNode.pb.h"

namespace model {

TaskNode CreateTaskNode(Task task);

TaskNode CreateTaskNode (Task task, TaskId parent_id);

TaskNode CreateTaskNode(TaskTransfer task);

}


#endif //SIMPLETASKMANAGER_TASKNODEFACTORYMETHOD_H
