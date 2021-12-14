//
// Created by Maksym Kharchenko on 14.12.2021.
//

#ifndef SIMPLETASKMANAGER_DUEDATEUTILITIES_H
#define SIMPLETASKMANAGER_DUEDATEUTILITIES_H

#include "Task.pb.h"

#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include <optional>
#include <google/protobuf/util/time_util.h>

std::optional<google::protobuf::Timestamp> StringToTime(const std::string& time_string, const std::string& format = "%H:%M %d.%m.%Y") {
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

std::string TimeToString(google::protobuf::Timestamp time, const std::string& format = "%H:%M %d.%m.%Y") {
    char buffer[32];
    time_t timet = google::protobuf::util::TimeUtil::TimestampToTimeT(time);
    std::tm *t = std::localtime(&timet);
    std::strftime(buffer, 32, format.c_str(), t);
    return buffer;
}

#endif //SIMPLETASKMANAGER_DUEDATEUTILITIES_H
