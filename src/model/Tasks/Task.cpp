//
// Created by Maksym Kharchenko on 08.11.2021.
//

#include "Task.h"

Task Task::Create(const std::string& title,
                  const Priority priority,
                  const time_t due_to,
                  const bool completed,
                  const std::string& label) {
    Task task(title, priority, due_to, completed, label);
    return task;
}

Task::Task(const std::string& title,
           const Priority priority,
           const time_t due_to,
           const bool completed,
           const std::string& label) {
    if (title.length() == 0){
        throw std::invalid_argument("Task title was empty.");
    }
    this->title_ = title;
    this->priority_ = priority;
    this->due_to_ = due_to;
    this->label_ = label;
    this->completed_ = completed;
}

std::string Task::to_string() {
    return title_ + ", Priority: " + PriorityToString(priority_) +
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

bool Task::IsCompleted() {
    return completed_;
}

std::string Task::GetLabel() {
    return label_;
}

bool Task::operator==(const Task& task) const {
    return this->title_ == task.title_ &&
        this->priority_ == task.priority_ &&
        this->due_to_ == task.due_to_ &&
        this->completed_ == task.completed_ &&
        this->label_ == task.label_;
}

TaskId Task::GetParentTaskId() {
    return TaskId::NullTaskId();
}

std::string Task::PriorityToString(Task::Priority priority) {
    std::string priority_string;
    switch (priority) {
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
    return priority_string;
}
