//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "WizardContext.h"

WizardContext::WizardContext() :
    editing_task_id_(std::nullopt) {

}

std::optional<Task> WizardContext::GetTask() {
    return task_builder_.BuildTask();
}

bool WizardContext::AddTaskTitle(const std::string& title) {
    task_builder_.SetTitle(title);
    return true;
}

bool WizardContext::AddTaskPriority(const Task::Priority priority) {
    task_builder_.SetPriority(priority);
    return true;
}

bool WizardContext::AddTaskDueTime(const DueTime due_time) {
    task_builder_.SetDueTime(due_time);
    return true;
}

void WizardContext::SetEditingTask(const TaskId& task_id, const Task& task) {
    editing_task_id_ = task_id;
    task_builder_ = task;
}

std::optional<TaskId> WizardContext::GetTaskId() {
    return editing_task_id_;
}
