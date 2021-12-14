//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "WizardContext.h"

WizardContext::WizardContext() :
    editing_task_id_(std::nullopt) {

}

std::optional<Task> WizardContext::GetTask() {
    if (task_.title().empty() || !task_.has_due_date()) {
        return std::nullopt;
    }
    return task_;
}

bool WizardContext::AddTaskTitle(const std::string& title) {
    if (title.empty()) {
        return false;
    }
    task_.set_title(title);
    return true;
}

bool WizardContext::AddTaskPriority(const Task::Priority priority) {
    task_.set_priority(priority);
    return true;
}

bool WizardContext::AddTaskDueTime(const google::protobuf::Timestamp due_time) {
    if (due_time.seconds() <= time(0)) {
        return false;
    }
    task_.set_allocated_due_date(new google::protobuf::Timestamp(due_time));
    return true;
}

void WizardContext::SetEditingTask(const TaskId& task_id, const Task& task) {
    editing_task_id_ = task_id;
    task_ = task;
}

std::optional<TaskId> WizardContext::GetTaskId() {
    return editing_task_id_;
}
