//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_WIZARDCONTEXT_H
#define SIMPLETASKMANAGER_WIZARDCONTEXT_H

#include "tasks/Task.h"
#include "TaskId.h"

#include <memory>
#include <string>
#include <optional>
#include <ctime>

class WizardContext {
public:
    WizardContext();
public: // Adding task information
    void AddTaskTitle(const std::string& title);
    void AddTaskPriority(Task::Priority priority);
    void AddTaskDueTime(time_t due_time);
    Task GetAddedTask();

    void SetEditingTaskId(const TaskId& task_id);
    void SetEditingTaskId(const std::string& task_id);
    TaskId GetEditingTaskId();
private:
    Task CreateDefaultTask();
    TaskId CreateDefaultTaskId();
private:
    Task added_task_;
    TaskId editing_task_id_;
};


#endif //SIMPLETASKMANAGER_WIZARDCONTEXT_H
