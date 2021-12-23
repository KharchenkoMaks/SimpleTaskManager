//
// Created by Maksym Kharchenko on 23.12.2021.
//

#ifndef SIMPLETASKMANAGER_TASKCONVERTORS_H
#define SIMPLETASKMANAGER_TASKCONVERTORS_H

#include "Task.pb.h"

#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include <optional>
#include <google/protobuf/util/time_util.h>

std::string TaskPriorityToString(Task::Priority priority);

std::optional<Task::Priority> StringToTaskPriority(const std::string& str);

std::optional<google::protobuf::Timestamp> StringToTime(const std::string& time_string, const std::string& format = "%H:%M %d.%m.%Y");

std::string TimeToString(google::protobuf::Timestamp time, const std::string& format = "%H:%M %d.%m.%Y");

std::string TaskToString(const TaskId& task_id, const Task& task);

std::optional<TaskId> StringToTaskId(const std::string& task_id_str);


#endif //SIMPLETASKMANAGER_TASKCONVERTORS_H
