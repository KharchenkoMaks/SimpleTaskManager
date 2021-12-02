//
// Created by Maksym Kharchenko on 08.11.2021.
//

#ifndef SIMPLETASKMANAGER_TASKMANAGER_H
#define SIMPLETASKMANAGER_TASKMANAGER_H

#include "IModel.h"
#include "tasks/Task.h"
#include "TaskId.h"
#include "IdGenerator.h"
#include "tasks/SubTask.h"

#include <map>
#include <vector>
#include <utility>
#include <memory>
#include <optional>

class TaskManager : public IModel {
public:
    std::optional<TaskId> AddTask(const Task& t) override;
    std::optional<TaskId> AddSubTask(const Task& task, const TaskId& parent_id) override;
    bool EditTask(const TaskId& id, const Task& t) override;
    bool DeleteTask(const TaskId& id) override;
    bool CompleteTask(const TaskId& id) override;

    std::vector<std::pair<TaskId, Task>> GetTasks() override;
public:
    bool IsTaskIdExist(const TaskId& task_id) override;

    std::optional<Task> GetTask(const TaskId& task_id) override;
public:
    explicit TaskManager(std::unique_ptr<IdGenerator> generator);
private:
    std::map<TaskId, Task> tasks_;
    std::map<TaskId, SubTask> subtasks_;

    std::unique_ptr<IdGenerator> generator_;
};


#endif //SIMPLETASKMANAGER_TASKMANAGER_H
