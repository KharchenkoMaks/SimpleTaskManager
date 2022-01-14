//
// Created by Maksym Kharchenko on 29.11.2021.
//

#include "TaskValidator.h"

bool TaskValidator::ValidateTask(const Task& task) {
    return ValidateTitle(task.title()) && ValidateDueDate(task.due_date());
}

bool TaskValidator::ValidateDueDate(google::protobuf::Timestamp due_date) {
    return due_date.seconds() > time(0);
}

bool TaskValidator::ValidateTitle(const std::string& title) {
    return !title.empty();
}
