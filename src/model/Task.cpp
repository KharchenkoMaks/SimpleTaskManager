//
// Created by Maksym Kharchenko on 08.11.2021.
//

#include "Task.h"

Task Task::Create(std::string title, Priority priority, time_t due_to) {
    Task task(title, priority, due_to);
    return task;
}

Task::Task(std::string title, Priority priority, time_t due_to) {
    if (title.length() == 0){
        throw std::invalid_argument("Task title was empty.");
    }
    this->title_ = title;
    this->priority_ = priority;
    this->due_to_ = due_to;
}