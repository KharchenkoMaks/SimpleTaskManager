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

void WizardContext::AddTaskTitle(const std::string &title) {
    added_task_ = Task::Create(title,
                               added_task_.GetPriority(),
                               added_task_.GetDueTime(),
                               added_task_.IsCompleted(),
                               added_task_.GetLabel());
}

void WizardContext::AddTaskPriority(const Task::Priority priority) {
    added_task_ = Task::Create(added_task_.GetTitle(),
                               priority,
                               added_task_.GetDueTime(),
                               added_task_.IsCompleted(),
                               added_task_.GetLabel());
}

void WizardContext::AddTaskDueTime(const time_t due_time) {
    added_task_ = Task::Create(added_task_.GetTitle(),
                               added_task_.GetPriority(),
                               due_time,
                               added_task_.IsCompleted(),
                               added_task_.GetLabel());
}

Task WizardContext::CreateDefaultTask() {
    return Task::Create("default_title", Task::Priority::NONE, 0);
}

void WizardContext::SetEditingTask(const TaskId& task_id, const Task& task) {
    editing_task_id_ = task_id;
    added_task_ = task;
}

TaskId WizardContext::CreateDefaultTaskId() {
    return TaskId::Create(0);
}

std::optional<TaskId> WizardContext::GetTaskId() const {
    return editing_task_id_;
}
