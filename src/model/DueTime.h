//
// Created by Maksym Kharchenko on 30.11.2021.
//

#ifndef SIMPLETASKMANAGER_DUETIME_H
#define SIMPLETASKMANAGER_DUETIME_H

#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

class DueTime {
public:
    static DueTime Create(time_t due_time);
    static DueTime Create(const std::string& due_time, const std::string& format = "%H:%M %d.%m.%Y");
public:
    std::string GetTimeString(const std::string& format = "%H:%M %d.%m.%Y") const;
    time_t GetTime() const;
public:
    bool operator== (const DueTime& due_time) const;
    bool operator< (const time_t& time) const;
private:
    DueTime(const std::string& due_time, const std::string& format);
    explicit DueTime(time_t due_time);
private:
    time_t StringToTime(const std::string& time_string, const std::string& format) const;
    std::string TimeToString(time_t time, const std::string& format) const;
private:
    time_t due_time_;
};


#endif //SIMPLETASKMANAGER_DUETIME_H
