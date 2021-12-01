//
// Created by Maksym Kharchenko on 08.11.2021.
//

#ifndef SIMPLETASKMANAGER_TASKMANAGER_H
#define SIMPLETASKMANAGER_TASKMANAGER_H

#include "tasks/Task.h"
#include "TaskId.h"
#include "IdGenerator.h"

#include <map>
#include <vector>
#include <utility>
#include <memory>
#include <optional>

class TaskManager {
public:
    std::optional<TaskId> Add(const Task& t);
    void Edit(const TaskId& id, const Task& t);
    void Delete(const TaskId& id);
    void Complete(const TaskId& id);

    std::vector<std::pair<TaskId, Task>> Show();
public:
    bool IsTaskIdExist(const TaskId& task_id) const;

    std::optional<Task> GetTask(const TaskId& task_id) const;
public:
    explicit TaskManager(std::unique_ptr<IdGenerator> generator);
private:
    std::map<TaskId, Task> tasks_;
    std::unique_ptr<IdGenerator> generator_;
};


#endif //SIMPLETASKMANAGER_TASKMANAGER_H
