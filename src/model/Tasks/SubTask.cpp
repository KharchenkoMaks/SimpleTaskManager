//
// Created by Maksym Kharchenko on 19.11.2021.
//

#include "Tasks/SubTask.h"

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
