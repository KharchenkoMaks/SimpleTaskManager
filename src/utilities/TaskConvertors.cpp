//
// Created by Maksym Kharchenko on 23.12.2021.
//

#include "TaskConvertors.h"

std::string TaskPriorityToString(const Task::Priority priority) {
    switch(priority) {
        case Task::Priority::Task_Priority_LOW:
            return "Low";
        case Task::Priority::Task_Priority_MEDIUM:
            return "Medium";
        case Task::Priority::Task_Priority_HIGH:
            return "High";
        default:
            return "None";
    }
}

std::optional<Task::Priority> StringToTaskPriority(const std::string& str) {
    if (str == "None" || str.empty()) {
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
                                + ", " + task.title()
                                + ", Priority: " + TaskPriorityToString(task.priority())
                                + ", Due to: " + TimeToString(task.due_date())
                                + ", Completed: ";
    if (task.completed()) {
        return_string += "Yes";
    } else {
        return_string += "No";
    }
    if (!task.label().empty()) {
        return_string += ", Labels:";
        for (const auto& label : task.label()) {
            return_string += " " + label + ",";
        }
        return_string.pop_back();
    }
    return return_string;
}

std::optional<TaskId> StringToTaskId(const std::string& task_id_str) {
    try {
        int id = std::stoi(task_id_str);
        if (id < 0)
            return std::nullopt;
        TaskId task_id;
        task_id.set_id(id);
        return task_id;
    } catch (std::invalid_argument) {
        return std::nullopt;
    }
}
