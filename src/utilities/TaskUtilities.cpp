//
// Created by Maksym Kharchenko on 14.12.2021.
//

#include "TaskUtilities.h"

std::string TaskPriorityToString(const Task::Priority priority) {
    switch(priority) {
        case Task::Priority::Task_Priority_LOW: {
            return "Low";
        }
        case Task::Priority::Task_Priority_MEDIUM: {
            return "Medium";
        }
        case Task::Priority::Task_Priority_HIGH: {
            return "High";
        }
        default: {
            return "None";
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
    } else if (str == "High") {
        return Task::Priority::Task_Priority_HIGH;
    } else {
        return std::nullopt;
    }
}

bool operator<(const TaskId& task_id1, const TaskId& task_id2) {
    return task_id1.id() < task_id2.id();
}

bool operator==(const TaskId& task_id1, const TaskId& task_id2) {
    return task_id1.id() == task_id2.id();
}

std::optional<google::protobuf::Timestamp> StringToTime(const std::string& time_string, const std::string& format) {
    std::tm t = { 0 };
    std::istringstream ss(time_string);
    ss >> std::get_time(&t, format.c_str());
    time_t some_time = mktime(&t);
    if (some_time >= 0 && t.tm_year > 0) {
        return google::protobuf::util::TimeUtil::TimeTToTimestamp(some_time);
    } else {
        return std::nullopt;
    }
}

std::string TimeToString(google::protobuf::Timestamp time, const std::string& format) {
    char buffer[32];
    time_t timet = google::protobuf::util::TimeUtil::TimestampToTimeT(time);
    std::tm *t = std::localtime(&timet);
    std::strftime(buffer, 32, format.c_str(), t);
    return buffer;
}

std::string TaskToString(const TaskId& task_id, const Task& task) {
    std::string return_string = "ID: " + std::to_string(task_id.id())
                                + ", Title: " + task.title()
                                + ", Priority: " + TaskPriorityToString(task.priority())
                                + ", Due to: " + TimeToString(task.due_date())
                                + ", Completed: ";
    if (task.completed()) {
        return_string += "Yes";
    } else {
        return_string += "No";
    }
    if (!task.label().empty()) {
        return_string += ", Label: " + task.label();
    }
    return return_string;
}

bool operator==(const Task& task1, const Task& task2) {
    return task1.title() == task2.title() &&
            task1.priority() == task2.priority() &&
            task1.due_date() == task2.due_date() &&
            task1.completed() == task2.completed() &&
            task1.label() == task2.label();
}

std::optional<TaskId> StringToTaskId(const std::string& task_id_str) {
    try {
        int id = std::stoi(task_id_str);
        TaskId task_id;
        task_id.set_id(id);
        return task_id;
    } catch (std::invalid_argument) {
        return std::nullopt;
    }
}

bool operator==(const TaskTransfer& task1, const TaskTransfer& task2) {
    if (task1.has_parent_id() && task2.has_parent_id()) {
        return task1.task_id() == task2.task_id() &&
            task1.task() == task2.task() &&
            task1.parent_id() == task2.parent_id();
    } else if (!task1.has_parent_id() && !task2.has_parent_id()) {
        return task1.task_id() == task2.task_id() &&
               task1.task() == task2.task();
    }
    return false;
}
