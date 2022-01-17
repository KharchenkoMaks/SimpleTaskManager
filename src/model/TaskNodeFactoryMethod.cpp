//
// Created by Maksym Kharchenko on 12.01.2022.
//

#include "TaskNodeFactoryMethod.h"

namespace model {

TaskNode CreateTaskNode(Task task) {
    TaskNode task_node;
    task_node.set_allocated_task(new Task(task));
    return task_node;
}

TaskNode CreateTaskNode(Task task, TaskId parent_id) {
    TaskNode task_node = CreateTaskNode(task);
    task_node.set_allocated_parent_id(new TaskId(parent_id));
    return task_node;
}

TaskNode CreateTaskNode(RelationalTask task) {
    if (task.has_parent_id()) {
        return CreateTaskNode(task.task(), task.parent_id());
    } else {
        return CreateTaskNode(task.task());
    }
}

}
