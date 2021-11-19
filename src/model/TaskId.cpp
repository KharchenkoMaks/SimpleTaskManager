//
// Created by Maksym Kharchenko on 10.11.2021.
//

#include "TaskId.h"

TaskId::TaskId(const int id) {
    this->id_ = id;
}

TaskId TaskId::Create(const int id) {
    if (id >= 0){
        return TaskId(id);
    } else{
        throw std::invalid_argument("Id was < 0");
    }
}

TaskId TaskId::Create(const std::string& id) {
    return TaskId::Create(std::stoi(id));
}

int TaskId::GetId() {
    return id_;
}

bool TaskId::operator==(const TaskId& t) const {
    return this->id_ == t.id_;
}

bool TaskId::operator<(const TaskId& t) const {
    return this->id_ < t.id_;
}
