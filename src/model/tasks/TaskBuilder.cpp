//
// Created by Maksym Kharchenko on 10.12.2021.
//

#include "TaskBuilder.h"

TaskBuilder::TaskBuilder() {
    ResetTask();
}

TaskBuilder& TaskBuilder::SetTitle(const std::string& title) {
    title_ = title;
    return *this;
}

TaskBuilder& TaskBuilder::SetPriority(const Task::Priority priority) {
    priority_ = priority;
    return *this;
}

TaskBuilder& TaskBuilder::SetDueTime(const DueTime& due_time) {
    due_time_ = due_time;
    return *this;
}

TaskBuilder& TaskBuilder::SetCompletionState(const bool completed) {
    completed_ = completed;
    return *this;
}

TaskBuilder& TaskBuilder::SetLabel(const std::string& label) {
    label_ = label;
    return *this;
}

std::optional<Task> TaskBuilder::BuildTask() {
    if (title_ == std::nullopt || due_time_ == std::nullopt) {
        return std::nullopt;
    }
    return Task::Create(title_.value(), priority_, due_time_.value(), completed_, label_);
}

TaskBuilder& TaskBuilder::operator=(const Task& task) {
    title_ = task.GetTitle();
    priority_ = task.GetPriority();
    due_time_ = task.GetDueTime();
    completed_ = task.IsCompleted();
    label_ = task.GetLabel();
    return *this;
}

void TaskBuilder::ResetTask() {
    title_ = std::nullopt;
    priority_ = Task::Priority::NONE;
    due_time_ = std::nullopt;
    completed_ = false;
    label_ = "";
}
