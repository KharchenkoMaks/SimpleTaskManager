//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "context/WizardContext.h"

WizardContext::WizardContext() :
    added_task_(CreateDefaultTask()),
    editing_task_id_(CreateDefaultTaskId()) {

}

Task WizardContext::GetAddedTask() {
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

// TODO (Maksym): Get Task by it's id and put in added_task_
// TODO: Method needs to be reworked!!!
void WizardContext::SetEditingTaskId(const TaskId& task_id) {
    editing_task_id_ = task_id;

    added_task_ = CreateDefaultTask();
}

void WizardContext::SetEditingTaskId(const std::string& task_id) {
    SetEditingTaskId(TaskId::Create(task_id));
}

TaskId WizardContext::GetEditingTaskId() {
    return editing_task_id_;
}

TaskId WizardContext::CreateDefaultTaskId() {
    return TaskId::Create(0);
}
