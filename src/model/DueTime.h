//
// Created by Maksym Kharchenko on 30.11.2021.
//

#ifndef SIMPLETASKMANAGER_DUETIME_H
#define SIMPLETASKMANAGER_DUETIME_H

#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include <optional>

class DueTime {
public:
    static DueTime Create(time_t due_time);
    static std::optional<DueTime> Create(const std::string& due_time, const std::string& format = "%H:%M %d.%m.%Y");
public:
    std::string GetTimeString(const std::string& format = "%H:%M %d.%m.%Y") const;
    time_t GetTime() const;
public:
    bool operator== (const DueTime& due_time) const;
    bool operator> (const time_t& time) const;
private:
    explicit DueTime(time_t due_time);
private:
    static std::optional<time_t> StringToTime(const std::string& time_string, const std::string& format);
    static std::string TimeToString(time_t time, const std::string& format);
private:
    time_t due_time_;
};


#endif //SIMPLETASKMANAGER_DUETIME_H
