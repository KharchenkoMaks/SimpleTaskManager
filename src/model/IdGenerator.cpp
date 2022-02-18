//
// Created by Maksym Kharchenko on 12.11.2021.
//

#include "IdGenerator.h"

TaskId IdGenerator::CreateNewTaskId() {
    TaskId task_id;
    task_id.set_id(++last_id_);
    return task_id;
}

IdGenerator::IdGenerator() : last_id_(0) {}

void IdGenerator::SetLastTaskId(const TaskId& task_id) {
    last_id_ = task_id.id();
}

IdGenerator::~IdGenerator() = default;
