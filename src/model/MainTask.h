//
// Created by Maksym Kharchenko on 14.12.2021.
//

#ifndef SIMPLETASKMANAGER_MAINTASK_H
#define SIMPLETASKMANAGER_MAINTASK_H

#include "Task.pb.h"

#include <map>
#include <utility>
#include <string>
#include <optional>

class MainTask {
public:
    static MainTask Create(const Task& task);
public:
    Task GetTask() const;
    std::optional<std::pair<TaskId, Task>> GetSubTask(const TaskId& task_id) const;
    std::vector<std::pair<TaskId, Task>> GetSubTasks() const;
public:
    void EditTask(const Task& task);
    void CompleteTask();
    void SetTaskLabel(const std::string& label);
public:
    void AddSubTask(const TaskId& task_id, const Task& subtask);
    bool EditSubTask(const TaskId& task_id, const Task& task);
    bool DeleteSubTask(const TaskId& task_id);
    bool CompleteSubTask(const TaskId& task_id);
    bool SetSubTaskLabel(const TaskId& task_id, const std::string& label);
    void CompleteAllSubTasks();
public:
    int SubTaskCount() const;
    bool ContainsSubTask(const TaskId& subtask_id) const;
    bool AreAllSubTasksCompleted() const;
private:
    explicit MainTask(const Task& task);
public:
    Task task_;
    std::map<TaskId, Task> subtasks_;
    std::map<TaskId, Task> deleted_subtasks_;
};


#endif //SIMPLETASKMANAGER_MAINTASK_H
