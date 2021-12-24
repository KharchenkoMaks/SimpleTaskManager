//
// Created by Maksym Kharchenko on 12.11.2021.
//

#include "IdGenerator.h"

TaskId IdGenerator::CreateNewTaskId() {
    TaskId task_id;
    task_id.set_id(last_id_++);
    return task_id;
}

IdGenerator::IdGenerator() : last_id_(0) {}

bool IdGenerator::SetLastTaskId(const TaskId& task_id) {
    if (task_id.id() >= 0) {
        last_id_ = task_id.id();
        return true;
    }
    return false;
}

IdGenerator::~IdGenerator() = default;
