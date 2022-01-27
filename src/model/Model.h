//
// Created by Maksym Kharchenko on 01.12.2021.
//

#ifndef SIMPLETASKMANAGER_MODEL_H
#define SIMPLETASKMANAGER_MODEL_H

#include "Task.pb.h"
#include "utilities/TaskActionResult.h"
#include "IdGenerator.h"

#include <optional>
#include <utility>

class Model {
public:
    virtual std::pair<TaskActionResult, TaskId> AddTask(const Task& task) = 0;
    virtual std::pair<TaskActionResult, TaskId> AddSubTask(const Task& task, const TaskId& parent_id) = 0;
    virtual TaskActionResult EditTask(const TaskId& id, const Task& t) = 0;
    virtual TaskActionResult DeleteTask(const TaskId& id, bool force_delete_subtasks) = 0;
    virtual TaskActionResult CompleteTask(const TaskId& id, bool force_complete_subtasks) = 0;
    virtual TaskActionResult AddTaskLabel(const TaskId& id, const std::string& label) = 0;
    virtual TaskActionResult RemoveTaskLabel(const TaskId& id, const std::string& label) = 0;

    virtual std::vector<RelationalTask> GetTasks() = 0;
    virtual std::vector<RelationalTask> GetTasksByLabel(const std::string& task_label) = 0;
    virtual std::optional<RelationalTask> GetTask(const TaskId& task_id) = 0;

    virtual bool IsTaskExist(const TaskId& task_id) = 0;

    virtual bool LoadModelState(const std::vector<RelationalTask>& tasks) = 0;

    virtual ~Model() = default;
};

#endif //SIMPLETASKMANAGER_MODEL_H
