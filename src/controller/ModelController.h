//
// Created by Maksym Kharchenko on 29.11.2021.
//

#ifndef SIMPLETASKMANAGER_MODELCONTROLLER_H
#define SIMPLETASKMANAGER_MODELCONTROLLER_H

#include "Task.pb.h"
#include "ControllerRequestResult.h"

#include <memory>
#include <utility>
#include <vector>

class ModelController {
public:
    virtual std::pair<ControllerRequestResult, TaskId> AddTask(const Task& task) = 0;
    virtual std::pair<ControllerRequestResult, TaskId> AddSubTask(const Task& task, const TaskId& parent_id) = 0;
    virtual ControllerRequestResult EditTask(const TaskId& task_id, const Task& task) = 0;
    virtual ControllerRequestResult DeleteTask(const TaskId& task_id) = 0;
    virtual ControllerRequestResult CompleteTask(const TaskId& task_id) = 0;
    virtual ControllerRequestResult AddTaskLabel(const TaskId& task_id, const std::string& label) = 0;
    virtual ControllerRequestResult RemoveTaskLabel(const TaskId& task_id, const std::string& label) = 0;

    virtual ControllerRequestResult DeleteTaskWithSubTasks(const TaskId& task_id) = 0;
    virtual ControllerRequestResult CompleteTaskWithSubTasks(const TaskId& task_id) = 0;

public:
    virtual std::vector<RelationalTask> GetAllTasks() = 0;
    virtual std::vector<RelationalTask> GetTasksByLabel(const std::string& task_label) = 0;
    virtual std::optional<RelationalTask> GetTask(const TaskId& task_id) = 0;

public:
    virtual ControllerRequestResult SaveToFile(const std::string& file_name) = 0;
    virtual ControllerRequestResult LoadFromFile(const std::string& file_name) = 0;

public:
    virtual ~ModelController() = default;
};


#endif //SIMPLETASKMANAGER_MODELCONTROLLER_H
