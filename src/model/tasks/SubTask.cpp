//
// Created by Maksym Kharchenko on 19.11.2021.
//

#include "SubTask.h"

TaskId SubTask::GetParentTaskId() const {
    return parent_;
}

SubTask SubTask::Create(const std::string &title,
                        Task::Priority priority,
                        DueTime due_to,
                        const TaskId &parent,
                        bool completed,
                        const std::string &label) {
    return SubTask(title, priority, due_to, parent, completed, label);
}

SubTask::SubTask(const std::string &title,
                 Task::Priority priority,
                 DueTime due_to,
                 const TaskId &parent,
                 bool completed,
                 const std::string &label) : task_(Task::Create(title, priority, due_to, completed, label)),
                                             parent_(parent) {

}

bool SubTask::operator==(const SubTask &task) const {
    return this->task_ == task.task_ &&
    this->parent_ == task.parent_;
}

SubTask SubTask::Create(const Task& task, const TaskId& parent) {
    return SubTask(task.GetTitle(), task.GetPriority(), task.GetDueTime(), parent, task.IsCompleted(), task.GetLabel());
}

Task SubTask::GetTaskParameters() const {
    return task_;
}
