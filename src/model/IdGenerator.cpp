//
// Created by Maksym Kharchenko on 12.11.2021.
//

#include "IdGenerator.h"

IdGenerator::IdGenerator() {
    this->last_id_ = 0;
}

TaskId IdGenerator::CreateNewTaskId() {
    return TaskId::Create(last_id_++);
}
