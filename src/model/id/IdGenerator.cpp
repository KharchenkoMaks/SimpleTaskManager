//
// Created by Maksym Kharchenko on 12.11.2021.
//

#include "IdGenerator.h"

IdGenerator::IdGenerator() {
    this->last_id_ = 0;
}


IdGenerator::IdGenerator(const int last_id) {
    if (last_id < 0){
        throw std::invalid_argument("last_id was < 0");
    }
    this->last_id_ = last_id;
}

TaskId IdGenerator::CreateNewTaskId() {
    return TaskId::Create(last_id_++).value();
}

IdGenerator::~IdGenerator() = default;