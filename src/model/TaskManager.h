//
// Created by Maksym Kharchenko on 08.11.2021.
//

#ifndef SIMPLETASKMANAGER_TASKMANAGER_H
#define SIMPLETASKMANAGER_TASKMANAGER_H

#include "Task.pb.h"
#include "MainTask.h"
#include "utilities/TaskIdUtilities.h"
#include "abstract_model/IModel.h"
#include "id/IdGenerator.h"
#include "utilities/TaskActionResult.h"

#include <map>
#include <vector>
#include <utility>
#include <memory>
#include <optional>
#include <algorithm>

class TaskManager : public IModel {
public:
    explicit TaskManager(std::unique_ptr<IdGenerator> generator);
public:
    std::pair<TaskActionResult, std::optional<TaskId>> AddTask(const Task& task) override;
    std::pair<TaskActionResult, std::optional<TaskId>> AddSubTask(const Task& task, const TaskId& parent_id) override;
    TaskActionResult EditTask(const TaskId& id, const Task& t) override;
    TaskActionResult DeleteTask(const TaskId& id, bool force_delete_subtasks = false) override;
    TaskActionResult CompleteTask(const TaskId& id, bool force_complete_subtasks = false) override;
    TaskActionResult SetTaskLabel(const TaskId& id, const std::string& label) override;

    std::vector<TaskTransfer> GetTasks() override;
    std::pair<TaskActionResult, std::vector<TaskTransfer>> GetTaskSubTasks(const TaskId& task_id) override;
    std::optional<TaskTransfer> GetTask(const TaskId& task_id) override;
public:
    bool IsTaskExist(const TaskId& task_id) override;
private:
    TaskTransfer CreateTaskTransferFromTask(const TaskId& task_id, const Task& task);
    TaskTransfer CreateTaskTransferFromSubTask(const TaskId& task_id, const Task& task, const TaskId& parent_id);
    std::vector<TaskTransfer> CreateTaskTransferFromMainTask(const TaskId& task_id, const MainTask& main_task);
    std::optional<std::map<TaskId, MainTask>::iterator> GetMainTaskWithSubTask(const TaskId& subtask_id);
private:
    std::map<TaskId, MainTask> tasks_;

    std::map<TaskId, MainTask> deleted_tasks_;

    std::unique_ptr<IdGenerator> generator_;
};


#endif //SIMPLETASKMANAGER_TASKMANAGER_H
