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

void StateContext::AddTaskTitle(const std::string& title) {
    task_.SetTitle(title);
}

void StateContext::AddTaskPriority(const Task::Priority priority) {
    task_.SetPriority(priority);
}

void StateContext::AddTaskDueTime(const google::protobuf::Timestamp& due_time) {
    task_.SetDueDate(due_time);
}

std::optional<TaskId> StateContext::GetTaskId() const {
    return task_id_;
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

void StateContext::SetCommand(std::unique_ptr<Command> command){
    command_ = std::move(command);
}

std::shared_ptr<Command> StateContext::GetCommand() const {
    return command_;
}

void StateContext::SetTaskId(const TaskId& task_id) {
    task_id_ = task_id;
}

void StateContext::SetTaskBuilder(const TaskBuilder& task_builder) {
    task_ = task_builder;
}

void StateContext::SetTasksToShow(const CommandResult::TasksToShow& tasks) {
    tasks_to_show_ = tasks;
}

CommandResult::TasksToShow StateContext::GetTasksToShow() const {
    return tasks_to_show_;
}
