//
// Created by Maksym Kharchenko on 29.11.2021.
//

#include "TaskValidator.h"

bool TaskValidator::ValidateTask(const Task& task) {
    return ValidateTitle(task.GetTitle()) && ValidateDueDate(task.GetDueTime());
}

bool TaskValidator::ValidateTaskId(const TaskId &task_id) {
    return task_id.GetId() >= 0;
}

bool TaskValidator::ValidateDueDate(DueTime due_date) {
    return time(0) <= due_date.GetTime();
}

bool TaskValidator::ValidateTitle(const std::string& title) {
    return !title.empty();
}
