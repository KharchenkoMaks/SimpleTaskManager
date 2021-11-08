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

std::string Task::to_string() {
    std::string priority_string = "";
    switch (priority_) {
        case Task::Priority::HIGH:{
            priority_string = "High";
            break;
        }
        case Task::Priority::MEDIUM:{
            priority_string = "Medium";
            break;
        }
        case Task::Priority::LOW:{
            priority_string = "Low";
            break;
        }
        case Task::Priority::NONE:{
            priority_string = "None";
            break;
        }
    }
    return title_ + ", Priority: " + priority_string +
                    ", Due to: " + std::to_string(due_to_) + "\n";
}

Task::Task() {}