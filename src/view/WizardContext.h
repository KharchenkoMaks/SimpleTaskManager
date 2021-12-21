//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_WIZARDCONTEXT_H
#define SIMPLETASKMANAGER_WIZARDCONTEXT_H

#include "Task.pb.h"

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
    virtual bool AddTaskDueTime(google::protobuf::Timestamp due_time);
    virtual std::optional<Task> GetTask() const;

    virtual void SetEditingTask(const TaskId& task_id, const Task& task);
    virtual std::optional<TaskId> GetTaskId() const;

    void SetTaskLabel(const std::string& task_label);
    std::string GetTaskLabel() const;

    void SetFileName(const std::string& file_name);
    std::string GetFileName() const;
public:
    virtual ~WizardContext() = default;
private:
    Task task_;
    std::optional<TaskId> editing_task_id_;

    std::string task_label_;
    std::string file_name_;
};


#endif //SIMPLETASKMANAGER_WIZARDCONTEXT_H
