//
// Created by Maksym Kharchenko on 02.12.2021.
//

#include "TaskTransfer.h"

TaskTransfer::TaskTransfer(const TaskId& task_id,
                           const Task& task,
                           const std::optional<TaskId>& parent_id) :
                           task_id_(task_id),
                           task_(task),
                           parent_id_(parent_id) {

}

TaskTransfer TaskTransfer::Create(const TaskId& task_id, const Task& task, const std::optional<TaskId>& parent_id) {
    return TaskTransfer(task_id, task, parent_id);
}

TaskId TaskTransfer::GetTaskId() const {
    return task_id_;
}

Task TaskTransfer::GetTask() const {
    return task_;
}

std::optional<TaskId> TaskTransfer::GetParentTaskId() const {
    return parent_id_;
}
