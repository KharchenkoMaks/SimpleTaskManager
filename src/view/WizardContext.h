//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_WIZARDCONTEXT_H
#define SIMPLETASKMANAGER_WIZARDCONTEXT_H

#include "tasks/Task.h"
#include "id/TaskId.h"
#include "DueTime.h"
#include "tasks/TaskBuilder.h"

#include <memory>
#include <string>
#include <optional>
#include <ctime>

class WizardContext {
public:
    WizardContext();
public:
    // Returns false if title isn't added
    virtual bool AddTaskTitle(const std::string& title);
    // Returns false if priority isn't added
    virtual bool AddTaskPriority(Task::Priority priority);
    // Returns false if due time isn't added
    virtual bool AddTaskDueTime(DueTime due_time);
    virtual std::optional<Task> GetTask();

    virtual void SetEditingTask(const TaskId& task_id, const Task& task);
    virtual std::optional<TaskId> GetTaskId();
public:
    virtual ~WizardContext() = default;
private:
    TaskBuilder task_builder_;
    std::optional<TaskId> editing_task_id_;
};


#endif //SIMPLETASKMANAGER_WIZARDCONTEXT_H
