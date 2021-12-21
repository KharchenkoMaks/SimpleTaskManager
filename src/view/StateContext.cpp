//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "StateContext.h"

StateContext::StateContext() :
    editing_task_id_(std::nullopt) {

}

std::optional<Task> StateContext::GetTask() const {
    if (task_.title().empty() || !task_.has_due_date()) {
        return std::nullopt;
    }
    return task_;
}

bool StateContext::AddTaskTitle(const std::string& title) {
    if (title.empty()) {
        return false;
    }
    task_.set_title(title);
    return true;
}

bool StateContext::AddTaskPriority(const Task::Priority priority) {
    task_.set_priority(priority);
    return true;
}

bool StateContext::AddTaskDueTime(const google::protobuf::Timestamp due_time) {
    if (due_time.seconds() <= time(0)) {
        return false;
    }
    task_.set_allocated_due_date(new google::protobuf::Timestamp(due_time));
    return true;
}

void StateContext::SetEditingTask(const TaskId& task_id, const Task& task) {
    editing_task_id_ = task_id;
    task_ = task;
}

std::optional<TaskId> StateContext::GetTaskId() const {
    return editing_task_id_;
}

void StateContext::SetTaskLabel(const std::string& task_label) {
    task_label_ = task_label;
}

std::string StateContext::GetTaskLabel() const {
    return task_label_;
}

void StateContext::SetFileName(const std::string& file_name) {
    file_name_ = file_name;
}

std::string StateContext::GetFileName() const {
    return file_name_;
}

void StateContext::SetCommand(std::unique_ptr<CommandInterface> command){
    command_ = std::move(command);
}

std::shared_ptr<CommandInterface> StateContext::GetCommand() const {
    return command_;
}

void StateContext::SetTaskId(const TaskId& task_id) {
    editing_task_id_.value().CopyFrom(task_id);
}
