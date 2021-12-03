//
// Created by Maksym Kharchenko on 10.11.2021.
//

#include "TaskId.h"

TaskId::TaskId(const int id) {
    this->id_ = id;
}

std::optional<TaskId> TaskId::Create(const int id) {
    if (id >= 0){
        return TaskId(id);
    } else {
        return std::nullopt;
    }
}

std::optional<TaskId> TaskId::Create(const std::string& id) {
    try {
        int casted_id = std::stoi(id);
        return TaskId::Create(casted_id);
    } catch (std::invalid_argument) {
        return std::nullopt;
    }
}

int TaskId::GetId() const {
    return id_;
}

bool TaskId::operator==(const TaskId& t) const {
    return this->id_ == t.id_;
}

bool TaskId::operator<(const TaskId& t) const {
    return this->id_ < t.id_;
}

std::string TaskId::to_string() const {
    return std::string("ID: " + std::to_string(id_));
}
