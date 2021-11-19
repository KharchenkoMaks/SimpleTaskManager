//
// Created by Maksym Kharchenko on 08.11.2021.
//

#ifndef SIMPLETASKMANAGER_TASK_H
#define SIMPLETASKMANAGER_TASK_H

#include <string>
#include <ctime>

class Task {
public:
    enum class Priority {
        HIGH,
        MEDIUM,
        LOW,
        NONE
    };
public:
    static Task Create(const std::string& title,
                       Priority priority, time_t due_to);
public:
    // throws std::runtime_eror if task is already completed
    void Complete();
    std::string to_string();
    // Getters
    std::string GetTitle();
    Task::Priority GetPriority();
    time_t GetDueTime();
    bool IsCompleted();
private:
    Task(const std::string& title, Priority priority, time_t due_to);
private:
    std::string title_;
    Priority priority_;
    time_t due_to_;
    bool completed_;
};


#endif //SIMPLETASKMANAGER_TASK_H
