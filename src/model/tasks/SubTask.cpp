//
// Created by Maksym Kharchenko on 19.11.2021.
//

#include "SubTask.h"

TaskId SubTask::GetParentTaskId() {
    return parent_;
}

SubTask SubTask::Create(const std::string &title,
                        Task::Priority priority,
                        time_t due_to,
                        const TaskId &parent,
                        bool completed,
                        const std::string &label) {
    return SubTask(title, priority, due_to, parent, completed, label);
}

SubTask::SubTask(const std::string &title,
                 Task::Priority priority,
                 time_t due_to,
                 const TaskId &parent,
                 bool completed,
                 const std::string &label) : Task(title, priority, due_to, completed, label), parent_(parent) {

}

bool SubTask::operator==(const SubTask &task) const {
    return this->title_ == task.title_ &&
        this->priority_ == task.priority_ &&
        this->due_to_ == task.due_to_ &&
        this->completed_ == task.completed_ &&
        this->label_ == task.label_ &&
        this->parent_ == parent_;
}
