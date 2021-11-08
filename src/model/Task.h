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

    Task();
    static Task Create(std::string title, Priority priority, time_t due_to);
private:
    std::string title_;
    Priority priority_;
    time_t due_to_;
    Task(std::string title, Priority priority, time_t due_to);
};


#endif //SIMPLETASKMANAGER_TASK_H
