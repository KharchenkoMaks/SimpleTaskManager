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
    std::optional<Task> GetTask() const;

    void SetEditingTask(const TaskId& task_id, const Task& task);
    std::optional<TaskId> GetTaskId() const;
private:
    Task CreateDefaultTask();
    TaskId CreateDefaultTaskId();

    void InitializeTask();
private:
    std::optional<Task> added_task_;
    std::optional<TaskId> editing_task_id_;
};


#endif //SIMPLETASKMANAGER_WIZARDCONTEXT_H
