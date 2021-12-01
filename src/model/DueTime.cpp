//
// Created by Maksym Kharchenko on 30.11.2021.
//

#include "DueTime.h"

std::optional<DueTime> DueTime::Create(const std::string& due_time, const std::string& format) {
    std::optional<time_t> converted_time = StringToTime(due_time, format);
    if (converted_time.has_value()) {
        return DueTime(converted_time.value());
    } else {
        return std::nullopt;
    }
}

std::optional<time_t> DueTime::StringToTime(const std::string& time_string, const std::string& format = "%H:%M %d.%m.%Y") {
    std::tm t;
    t.tm_sec = 0;
    std::istringstream ss(time_string);
    ss >> std::get_time(&t, format.c_str());
    time_t some_time = mktime(&t);
    if (some_time >= 0 && t.tm_year < 1000) {
        return some_time;
    } else {
        throw std::invalid_argument("Time string format was wrong!");
    }
}

std::string DueTime::TimeToString(time_t time, const std::string& format = "%H:%M %d.%m.%Y") {
    char buffer[32];
    std::tm *t = std::localtime(&time);
    std::strftime(buffer, 32, format.c_str(), t);
    return buffer;
}

std::string DueTime::GetTimeString(const std::string& format) const {
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

bool DueTime::operator==(const DueTime &due_time) const {
    return this->due_time_ == due_time.due_time_;
}

bool DueTime::operator>(const time_t &time) const {
    return this->due_time_ > time;
}
