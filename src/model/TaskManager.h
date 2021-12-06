//
// Created by Maksym Kharchenko on 08.11.2021.
//

#ifndef SIMPLETASKMANAGER_TASKMANAGER_H
#define SIMPLETASKMANAGER_TASKMANAGER_H

#include "abstract_model/IModel.h"
#include "abstract_model/TaskTransfer.h"
#include "tasks/Task.h"
#include "id/TaskId.h"
#include "id/IdGenerator.h"
#include "tasks/SubTask.h"

#include <map>
#include <vector>
#include <utility>
#include <memory>
#include <optional>
#include <algorithm>

class TaskManager : public IModel {
public:
    std::optional<TaskId> AddTask(const Task& t) override;
    std::optional<TaskId> AddSubTask(const Task& task, const TaskId& parent_id) override;
    bool EditTask(const TaskId& id, const Task& t) override;
    bool DeleteTask(const TaskId& id, bool force_delete_subtasks = false) override;
    bool CompleteTask(const TaskId& id, bool force_complete_subtasks = false) override;
    bool SetTaskLabel(const TaskId& id, std::string& label) override;

    std::vector<TaskTransfer> GetTasks() override;
    std::optional<std::vector<TaskTransfer>> GetTaskSubTasks(const TaskId& task_id) override;
public:
    bool IsTaskIdExist(const TaskId& task_id) override;

    std::optional<TaskTransfer> GetTask(const TaskId& task_id) override;
public:
    explicit TaskManager(std::unique_ptr<IdGenerator> generator);

private:
    enum class TaskType {
        kParent,
        kChild,
        kDeleted,
        kNone
    };
private:
    TaskType GetTaskType(const TaskId& task_id) const;
    std::optional<SubTask> GetSubTaskById(const TaskId& task_id) const;
    std::optional<Task> GetTaskById(const TaskId& task_id) const;

    std::optional<std::vector<TaskId>> GetAllTaskSubTaskIds(const TaskId& parent_id);

    Task MakeTaskCompleted(const Task& task);
    Task SetLabel(const Task& task, const std::string& label);
private:
    void DeleteSubTasks(const TaskId& parent_id);
    bool IsAllSubTasksDeleted(const TaskId& parent_id);
private:
    std::map<TaskId, Task> tasks_;
    std::map<TaskId, SubTask> subtasks_;

    std::map<TaskId, Task> deleted_tasks_;
    std::map<TaskId, SubTask> deleted_subtasks_;

    std::unique_ptr<IdGenerator> generator_;
};


#endif //SIMPLETASKMANAGER_TASKMANAGER_H
