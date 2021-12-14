//
// Created by Maksym Kharchenko on 14.12.2021.
//

#ifndef SIMPLETASKMANAGER_TASKUTILITIES_H
#define SIMPLETASKMANAGER_TASKUTILITIES_H

#include "Task.pb.h"

#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include <optional>
#include <google/protobuf/util/time_util.h>

std::string TaskPriorityToString(Task::Priority priority);

std::optional<Task::Priority> StringToTaskPriority(const std::string& str);

bool operator<(const TaskId& task_id1, const TaskId& task_id2);

bool operator==(const TaskId& task_id1, const TaskId& task_id2);

std::optional<google::protobuf::Timestamp> StringToTime(const std::string& time_string, const std::string& format = "%H:%M %d.%m.%Y");

std::string TimeToString(google::protobuf::Timestamp time, const std::string& format = "%H:%M %d.%m.%Y");

std::string TaskToString(const TaskId& task_id, const Task& task);

#endif //SIMPLETASKMANAGER_TASKUTILITIES_H
