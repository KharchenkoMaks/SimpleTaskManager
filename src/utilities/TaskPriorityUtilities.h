//
// Created by Maksym Kharchenko on 14.12.2021.
//

#ifndef SIMPLETASKMANAGER_TASKPRIORITYUTILITIES_H
#define SIMPLETASKMANAGER_TASKPRIORITYUTILITIES_H

#include "Task.pb.h"

#include <string>
#include <optional>

std::string TaskPriorityToString(const Task::Priority priority) {
    switch(priority) {
        case Task::Priority::Task_Priority_NONE: {
            return "None";
        }
        case Task::Priority::Task_Priority_LOW: {
            return "Low";
        }
        case Task::Priority::Task_Priority_MEDIUM: {
            return "Medium";
        }
        case Task::Priority::Task_Priority_HIGH: {
            return "High";
        }
    }
}

std::optional<Task::Priority> StringToTaskPriority(const std::string& str) {
    if (str == "None") {
        return Task::Priority::Task_Priority_NONE;
    } else if (str == "Low") {
        return Task::Priority::Task_Priority_LOW;
    } else if (str == "Medium") {
        return Task::Priority::Task_Priority_MEDIUM;
    } if (str == "High") {
        return Task::Priority::Task_Priority_HIGH;
    }
}

#endif //SIMPLETASKMANAGER_TASKPRIORITYUTILITIES_H
