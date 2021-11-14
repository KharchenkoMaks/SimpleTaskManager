//
// Created by Maksym Kharchenko on 08.11.2021.
//

#include "Task.h"

Task Task::Create(const std::string& title, const Priority& priority, const time_t& due_to) {
    Task task(title, priority, due_to);
    return task;
}

Task::Task(const std::string& title, const Priority& priority, const time_t& due_to) {
    if (title.length() == 0){
        throw std::invalid_argument("Task title was empty.");
    }
    this->title_ = title;
    this->priority_ = priority;
    this->due_to_ = due_to;
}

std::string Task::to_string() {
    std::string priority_string;
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

std::string Task::GetTitle() {
    return this->title_;
}

Task::Priority Task::GetPriority() {
    return this->priority_;
}

time_t Task::GetDueTime() {
    return this->due_to_;
}
