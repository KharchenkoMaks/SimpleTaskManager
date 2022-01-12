//
// Created by Maksym Kharchenko on 12.01.2022.
//

#include "TaskNodeFactoryMethod.h"

using namespace model;

TaskNode Create(Task task) {
    TaskNode task_node;
    task_node.set_allocated_task(new Task(task));
}

TaskNode Create (Task task, TaskId parent_id) {
    TaskNode task_node = ::Create(task);
    task_node.set_allocated_parent_id(new TaskId(parent_id));
}
