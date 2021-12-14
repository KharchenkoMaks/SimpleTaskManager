//
// Created by Maksym Kharchenko on 14.12.2021.
//

#include "MainTask.h"
#include "utilities/TaskUtilities.h"

MainTask::MainTask(const Task& task) {
    task_.CopyFrom(task);
}

MainTask MainTask::Create(const Task& task) {
    return MainTask(task);
}

void MainTask::AddSubTask(const TaskId& task_id, const Task& subtask) {
    subtasks_.insert_or_assign(task_id, subtask);
}

bool MainTask::ContainsSubTask(const TaskId& subtask_id) const {
    return subtasks_.find(subtask_id) != subtasks_.end();
}

bool MainTask::EditSubTask(const TaskId& task_id, const Task& task) {
    auto subtask = subtasks_.find(task_id);
    if (subtask == subtasks_.end()) {
        return false;
    }
    subtask->second.CopyFrom(task);
    return true;
}

void MainTask::EditTask(const Task &task) {
    task_.CopyFrom(task);
}

int MainTask::SubTaskCount() const {
    return subtasks_.size();
}

bool MainTask::DeleteSubTask(const TaskId& task_id) {
    auto subtask = subtasks_.find(task_id);
    if (subtask == subtasks_.end()) {
        return false;
    }
    subtasks_.erase(subtask);
    deleted_subtasks_.insert_or_assign(subtask->first, subtask->second);
    return true;
}

bool MainTask::AreAllSubTasksCompleted() const {
    for (const auto& subtask : subtasks_) {
        if (!subtask.second.completed()) {
            return false;
        }
    }
    return true;
}

void MainTask::CompleteAllSubTasks() {
    for (auto item = subtasks_.begin(); item != subtasks_.end(); item++) {
        item->second.set_completed(true);
    }
}

bool MainTask::CompleteSubTask(const TaskId &task_id) {
    auto subtask = subtasks_.find(task_id);
    if (subtask == subtasks_.end()) {
        return false;
    }
    subtask->second.set_completed(true);
    return true;
}

void MainTask::CompleteTask() {
    task_.set_completed(true);
}

bool MainTask::SetSubTaskLabel(const TaskId &task_id, const std::string& label) {
    auto subtask = subtasks_.find(task_id);
    if (subtask == subtasks_.end()) {
        return false;
    }
    subtask->second.set_label(label);
    return true;
}

void MainTask::SetTaskLabel(const std::string& label) {
    task_.set_label(label);
}

Task MainTask::GetTask() const {
    return task_;
}

std::vector<std::pair<TaskId, Task>> MainTask::GetSubTasks() const {
    std::vector<std::pair<TaskId, Task>> subtasks;
    for (const auto& subtask : subtasks_) {
        subtasks.emplace_back(subtask.first, subtask.second);
    }
    return subtasks;
}

std::optional<std::pair<TaskId, Task>> MainTask::GetSubTask(const TaskId& task_id) const {
    auto subtask = subtasks_.find(task_id);
    if (subtask == subtasks_.end()) {
        return std::nullopt;
    }
    return std::pair(subtask->first, subtask->second);
}
