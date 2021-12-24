//
// Created by Maksym Kharchenko on 22.12.2021.
//

#include "TaskBuilder.h"

TaskBuilder TaskBuilder::Create() {
    TaskBuilder builder;
    return builder;
}

TaskBuilder& TaskBuilder::SetTitle(const std::string& title) {
    title_ = title;
    return *this;
}

TaskBuilder& TaskBuilder::SetPriority(Task::Priority priority) {
    priority_ = priority;
    return *this;
}

TaskBuilder& TaskBuilder::SetDueDate(const google::protobuf::Timestamp& due_date) {
    due_date_ = due_date;
    return *this;
}

TaskBuilder& TaskBuilder::SetCompletion(bool is_completed) {
    is_completed_ = is_completed;
    return *this;
}

TaskBuilder& TaskBuilder::SetLabel(const std::string &label) {
    label_ = label;
    return *this;
}

TaskBuilder& TaskBuilder::Merge(const Task& task) {
    if (!title_.has_value())
        title_ = task.title();
    else if (!priority_.has_value())
        priority_ = task.priority();
    else if (!due_date_.has_value())
        due_date_ = task.due_date();
    else if (!is_completed_.has_value())
        is_completed_ = task.completed();
    else if (!label_.has_value())
        label_ = task.label();

    return *this;
}

Task TaskBuilder::BuildTask() const {
    Task task;
    task.set_title(title_.value_or(""));
    task.set_priority(priority_.value_or(Task::Priority::Task_Priority_NONE));
    task.set_completed(is_completed_.value_or(false));
    task.set_label(label_.value_or(""));
    if (due_date_.has_value())
        task.set_allocated_due_date(new google::protobuf::Timestamp(due_date_.value()));
    return task;
}

void TaskBuilder::operator=(const TaskBuilder& task_builder) {
    title_ = task_builder.title_;
    priority_ = task_builder.priority_;
    due_date_ = task_builder.due_date_;
    is_completed_ = task_builder.is_completed_;
    label_ = task_builder.label_;
}
