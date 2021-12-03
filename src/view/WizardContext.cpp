//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "WizardContext.h"

WizardContext::WizardContext() :
    added_task_(std::nullopt),
    editing_task_id_(std::nullopt) {

}

std::optional<Task> WizardContext::GetTask() const {
    return added_task_;
}

bool WizardContext::AddTaskTitle(const std::string &title) {
    if (title.empty()){
        return false;
    }
    InitializeTask();
    added_task_ = Task::Create(title,
                               added_task_.value().GetPriority(),
                               added_task_.value().GetDueTime(),
                               added_task_.value().IsCompleted(),
                               added_task_.value().GetLabel());
    return true;
}

bool WizardContext::AddTaskPriority(const Task::Priority priority) {
    InitializeTask();
    added_task_ = Task::Create(added_task_.value().GetTitle(),
                               priority,
                               added_task_.value().GetDueTime(),
                               added_task_.value().IsCompleted(),
                               added_task_.value().GetLabel());
    return true;
}

bool WizardContext::AddTaskDueTime(const DueTime due_time) {
    if (due_time > time(0)) {
        InitializeTask();
        added_task_ = Task::Create(added_task_.value().GetTitle(),
                                   added_task_.value().GetPriority(),
                                   due_time,
                                   added_task_.value().IsCompleted(),
                                   added_task_.value().GetLabel());
        return true;
    } else {
        return false;
    }
}

Task WizardContext::CreateDefaultTask() {
    return Task::Create("default_title", Task::Priority::NONE, DueTime::Create(0));
}

void WizardContext::SetEditingTask(const TaskId& task_id, const Task& task) {
    editing_task_id_ = task_id;
    added_task_ = task;
}

TaskId WizardContext::CreateDefaultTaskId() {
    return TaskId::Create(0).value();
}

std::optional<TaskId> WizardContext::GetTaskId() const {
    return editing_task_id_;
}

void WizardContext::InitializeTask() {
    if (!added_task_.has_value()){
        added_task_ = CreateDefaultTask();
    }
}
