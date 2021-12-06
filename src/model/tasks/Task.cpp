//
// Created by Maksym Kharchenko on 08.11.2021.
//

#include "Task.h"

Task Task::Create(const std::string& title,
                  const Priority priority,
                  const DueTime due_to,
                  const bool completed,
                  const std::string& label) {
    Task task(title, priority, due_to, completed, label);
    return task;
}

Task::Task(const std::string& title,
           const Priority priority,
           const DueTime due_to,
           const bool completed,
           const std::string& label) :
           title_(title),
           priority_(priority),
           due_to_(due_to),
           completed_(completed),
           label_(label) {

}

std::string Task::to_string() const {
    std::string answer = title_ + ", Priority: " + PriorityToString(priority_) +
                    ", Due to: " + due_to_.GetTimeString();
    if (IsCompleted()) {
        answer += ", Completed: Yes";
    } else {
        answer += ", Completed: No";
    }

    if (!label_.empty()) {
        answer += ",Label: " + label_;
    }
    return answer;
}

std::string Task::GetTitle() const {
    return this->title_;
}

Task::Priority Task::GetPriority() const {
    return this->priority_;
}

DueTime Task::GetDueTime() const {
    return this->due_to_;
}

bool Task::IsCompleted() const {
    return completed_;
}

std::string Task::GetLabel() const {
    return label_;
}

bool Task::operator==(const Task& task) const {
    return this->title_ == task.title_ &&
        this->priority_ == task.priority_ &&
        this->due_to_ == task.due_to_ &&
        this->completed_ == task.completed_ &&
        this->label_ == task.label_;
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
            priority_string = "kNone";
            break;
        }
    }
    return priority_string;
}

std::optional<Task::Priority> Task::GetTaskPriority(const std::string& priority) {
    if (priority == "High"){
        return Priority::HIGH;
    } else if (priority == "Medium"){
        return Priority::MEDIUM;
    } else if (priority == "Low"){
        return Priority::LOW;
    } else if (priority == "kNone"){
        return Priority::NONE;
    } else {
        return std::nullopt;
    }
}
