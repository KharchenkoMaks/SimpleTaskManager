//
// Created by Maksym Kharchenko on 30.11.2021.
//

#include "DueTime.h"

DueTime DueTime::Create(const std::string& due_time, const std::string& format = "%H:%M %d.%m.%Y") {
    return DueTime(due_time, format);
}

DueTime::DueTime(const std::string& due_time, const std::string& format) {
    due_time_ = StringToTime(due_time, format);
}

time_t DueTime::StringToTime(const std::string& time_string, const std::string& format = "%H:%M %d.%m.%Y") const {
    struct std::tm tm;
    std::istringstream ss(time_string);
    ss >> std::get_time(&tm, format.c_str());
    time_t some_time = mktime(&tm);
    return some_time;
}

std::string DueTime::TimeToString(time_t time, const std::string& format = "%H:%M %d.%m.%Y") const {
    char buffer[32];
    std::tm *t = std::localtime(&time);
    std::strftime(buffer, 32, format.c_str(), t);
    return buffer;
}

std::string DueTime::GetTimeString(const std::string& format = "%H:%M %d.%m.%Y") const {
    return TimeToString(due_time_, format);
}

time_t DueTime::GetTime() const {
    return due_time_;
}

DueTime DueTime::Create(time_t time) {
    return DueTime(time);
}

DueTime::DueTime(time_t due_time) : due_time_(due_time) {

}
