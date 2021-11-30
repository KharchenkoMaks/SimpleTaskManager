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
    static DueTime Create(const std::string& due_time, const std::string& format);
public:
    std::string GetTimeString(const std::string& format) const;
    time_t GetTime() const;
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
