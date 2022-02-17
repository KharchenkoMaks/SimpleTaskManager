//
// Created by Maksym Kharchenko on 08.11.2021.
//

#ifndef SIMPLETASKMANAGER_TASKMANAGER_H
#define SIMPLETASKMANAGER_TASKMANAGER_H

#include "Task.pb.h"
#include "TaskNode.pb.h"
#include "Model.h"
#include "IdGenerator.h"
#include "utilities/TaskActionResult.h"
#include "utilities/TaskValidator.h"

#include <map>
#include <vector>
#include <utility>
#include <memory>
#include <optional>
#include <algorithm>
#include <mutex>

class TaskManager : public Model {
public:
    explicit TaskManager(std::unique_ptr<IdGenerator> generator);
    TaskManager(std::unique_ptr<IdGenerator> generator, std::unique_ptr<TaskValidator> task_validator);
public:
    std::pair<TaskActionResult, TaskId> AddTask(const Task& task) override;
    std::pair<TaskActionResult, TaskId> AddSubTask(const Task& task, const TaskId& parent_id) override;
    TaskActionResult EditTask(const TaskId& id, const Task& task) override;
    TaskActionResult DeleteTask(const TaskId& id, bool force_delete_subtasks) override;
    TaskActionResult CompleteTask(const TaskId& id, bool force_complete_subtasks) override;
    TaskActionResult AddTaskLabel(const TaskId& id, const std::string& label) override;
    TaskActionResult RemoveTaskLabel(const TaskId& id, const std::string& label) override;

    std::vector<RelationalTask> GetTasks() override;
    std::vector<RelationalTask> GetTasksByLabel(const std::string& task_label) override;
    std::optional<RelationalTask> GetTask(const TaskId& task_id) override;
public: // Persistence
    bool LoadModelState(const std::vector<RelationalTask>& tasks) override;
private:
    RelationalTask CreateRelationalTask(const std::map<TaskId, model::TaskNode>::iterator task);
    RelationalTask CreateRelationalTask(const TaskId& id, const model::TaskNode& task_node);
    std::vector<RelationalTask> GetAllTaskChildren(const TaskId& task_id);

    google::protobuf::internal::RepeatedPtrIterator<const std::string> FindTaskLabel(const Task& task, const std::string& label);
private:
    std::map<TaskId, model::TaskNode> tasks_;
    std::mutex tasks_map_mutex_;

    std::map<TaskId, model::TaskNode> deleted_tasks_;

    std::unique_ptr<IdGenerator> generator_;
    std::unique_ptr<TaskValidator> task_validator_;
};


#endif //SIMPLETASKMANAGER_TASKMANAGER_H
