//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "StateContext.h"

StateContext::StateContext() :
        task_id_(std::nullopt),
        task_(TaskBuilder::Create()) {

}

TaskBuilder StateContext::GetTaskBuilder() const {
    return task_;
}

bool StateContext::AddTaskTitle(const std::string& title) {
    if (title.empty()) {
        return false;
    }
    task_.SetTitle(title);
    return true;
}

bool StateContext::AddTaskPriority(const Task::Priority priority) {
    task_.SetPriority(priority);
    return true;
}

bool StateContext::AddTaskDueTime(const google::protobuf::Timestamp& due_time) {
    if (due_time.seconds() <= time(0)) {
        return false;
    }
    task_.SetDueDate(due_time);
    return true;
}

std::optional<TaskId> StateContext::GetTaskId() const {
    return task_id_;
}

void StateContext::AddTaskLabel(const std::string& task_label) {
    task_.SetLabel(task_label);
}

std::string StateContext::GetTaskLabel() const {
    return task_.BuildTask().label();
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
    task_id_.value().CopyFrom(task_id);
}

void StateContext::SetTaskBuilder(const TaskBuilder& task_builder) {
    task_ = task_builder;
}
