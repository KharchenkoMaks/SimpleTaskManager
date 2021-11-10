//
// Created by Maksym Kharchenko on 10.11.2021.
//

#include "TaskId.h"

TaskId::TaskId(int id) {
    if (id >= 0){
        this->id_ = id;
    } else{
        throw std::invalid_argument("Id was < 0");
    }
}

TaskId TaskId::Create(int id) {
    return TaskId(id);
}

TaskId TaskId::Create(std::string id) {
    return TaskId(std::stoi(id));
}
