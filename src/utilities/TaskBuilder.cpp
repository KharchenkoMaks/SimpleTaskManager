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

TaskBuilder& TaskBuilder::AddLabel(const std::string& label) {
    labels_.push_back(label);
    return *this;
}

TaskBuilder& TaskBuilder::Merge(const Task& task) {
    if (!title_.has_value())
        title_ = task.title();
    if (!priority_.has_value())
        priority_ = task.priority();
    if (!due_date_.has_value())
        due_date_ = task.due_date();
    if (!is_completed_.has_value())
        is_completed_ = task.completed();
    if (labels_.empty()) {
        for (int i = 0; i < task.label_size(); ++i) {
            labels_.push_back(task.label(i));
        }
    }

    return *this;
}

Task TaskBuilder::BuildTask() const {
    Task task;
    task.set_title(title_.value_or(""));
    task.set_priority(priority_.value_or(Task::Priority::Task_Priority_NONE));
    task.set_completed(is_completed_.value_or(false));
    for (const auto& label : labels_) {
        task.add_label(label);
    }
    if (due_date_.has_value())
        task.set_allocated_due_date(new google::protobuf::Timestamp(due_date_.value()));
    return task;
}

void TaskBuilder::operator=(const TaskBuilder& task_builder) {
    title_ = task_builder.title_;
    priority_ = task_builder.priority_;
    due_date_ = task_builder.due_date_;
    is_completed_ = task_builder.is_completed_;
    labels_ = task_builder.labels_;
}
