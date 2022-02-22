//
// Created by Maksym Kharchenko on 12.11.2021.
//

#include "SequentIdGenerator.h"

TaskId SequentIdGenerator::CreateNewTaskId() {
    TaskId task_id;
    task_id.set_id(++last_id_);
    return task_id;
}

SequentIdGenerator::SequentIdGenerator() : last_id_(0) {}

void SequentIdGenerator::SetLastTaskId(const TaskId& task_id) {
    last_id_ = task_id.id();
}
