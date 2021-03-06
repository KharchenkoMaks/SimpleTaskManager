//
// Created by Maksym Kharchenko on 08.11.2021.
//

#include "TaskManager.h"
#include "utilities/TaskComparators.h"
#include "TaskNodeFactoryMethod.h"

#include "logs/DefaultLogging.h"

using namespace model;

TaskManager::TaskManager(std::unique_ptr<IdGenerator> generator) :
                        generator_(std::move(generator)),
                        task_validator_(std::make_unique<TaskValidator>()) {

}

TaskManager::TaskManager(std::unique_ptr<IdGenerator> generator,
                         std::unique_ptr<TaskValidator> task_validator) :
        generator_(std::move(generator)),
        task_validator_(std::move(task_validator)) {

}

std::pair<TaskActionResult, TaskId> TaskManager::AddTask(const Task& task) {
    if (!task_validator_->ValidateTask(task)) {
        LOG_TRIVIAL(error) << "Invalid task given, Task: " << task.ShortDebugString();
        return std::pair(TaskActionResult::FAIL_INVALID_TASK, TaskId::default_instance());
    }

    TaskId task_id = generator_->CreateNewTaskId();
    {
        std::lock_guard<std::mutex> guard(tasks_map_mutex_);
        tasks_.insert({task_id, model::CreateTaskNode(task)});
    }
    LOG_TRIVIAL(debug) << "Task added, " << task_id.ShortDebugString();

    return std::pair(TaskActionResult::SUCCESS, task_id);
}

std::pair<TaskActionResult, TaskId> TaskManager::AddSubTask(const Task& task, const TaskId& parent_id) {
    if (!task_validator_->ValidateTask(task)) {
        LOG_TRIVIAL(error) << "Invalid task given, Task: " << task.ShortDebugString();
        return std::pair(TaskActionResult::FAIL_INVALID_TASK, TaskId::default_instance());
    }
    TaskId subtask_id;
    {
        std::lock_guard<std::mutex> guard(tasks_map_mutex_);

        auto parent_task = tasks_.find(parent_id);
        if (parent_task == tasks_.end()) {
            LOG_TRIVIAL(warning) << "No such task found, " << parent_id.ShortDebugString();
            return std::pair(TaskActionResult::FAIL_NO_SUCH_TASK, TaskId::default_instance());
        }

        subtask_id = generator_->CreateNewTaskId();
        tasks_.insert({subtask_id, model::CreateTaskNode(task, parent_id)});
    }
    LOG_TRIVIAL(debug) << "Task added, " << subtask_id.ShortDebugString();

    return std::pair(TaskActionResult::SUCCESS, subtask_id);
}

TaskActionResult TaskManager::EditTask(const TaskId& id, const Task& task) {
    if (!task_validator_->ValidateTask(task)) {
        return TaskActionResult::FAIL_INVALID_TASK;
    }

    std::lock_guard<std::mutex> guard(tasks_map_mutex_);

    auto editing_task = tasks_.find(id);
    if (editing_task == tasks_.end())
        return TaskActionResult::FAIL_NO_SUCH_TASK;

    editing_task->second.set_allocated_task(new Task(task));
    return TaskActionResult::SUCCESS;
}

TaskActionResult TaskManager::DeleteTask(const TaskId& id, bool force_delete_subtasks) {
    std::lock_guard<std::mutex> guard(tasks_map_mutex_);

    std::vector<TaskId> task_ids_to_delete;
    auto task_to_delete = tasks_.find(id);

    if (task_to_delete == tasks_.end())
        return TaskActionResult::FAIL_NO_SUCH_TASK;
    else
        task_ids_to_delete.push_back(task_to_delete->first);

    if (!force_delete_subtasks && std::find_if(tasks_.begin(), tasks_.end(), [&id](const std::pair<TaskId, TaskNode>& task) {
        return task.second.parent_id() == id;
    }) != tasks_.end()) {
        return TaskActionResult::FAIL_NOT_DELETED_SUBTASKS;
    }

    for (size_t i = 0; i < task_ids_to_delete.size(); ++i) {
        for (const auto& task : tasks_) {
            if (task.second.parent_id() == task_ids_to_delete[i]) {
                task_ids_to_delete.push_back(task.first);
            }
        }
        auto deleting_task = tasks_.find(task_ids_to_delete[i]);
        deleted_tasks_.insert_or_assign(deleting_task->first, deleting_task->second);
        tasks_.erase(deleting_task);
    }

    return TaskActionResult::SUCCESS;
}

TaskActionResult TaskManager::CompleteTask(const TaskId& id, bool force_complete_subtasks) {
    std::lock_guard<std::mutex> guard(tasks_map_mutex_);

    std::vector<TaskId> task_ids_to_complete;
    auto task_to_complete = tasks_.find(id);

    if (task_to_complete == tasks_.end())
        return TaskActionResult::FAIL_NO_SUCH_TASK;
    else
        task_ids_to_complete.push_back(task_to_complete->first);

    if (!force_complete_subtasks && std::find_if(tasks_.begin(), tasks_.end(), [&id](const std::pair<TaskId, TaskNode>& task) {
        return task.second.parent_id() == id && !task.second.task().completed();
    }) != tasks_.end()) {
        return TaskActionResult::FAIL_UNCOMPLETED_SUBTASKS;
    }

    for (size_t i = 0; i < task_ids_to_complete.size(); ++i) {
        for (const auto& task : tasks_) {
            if (task.second.parent_id() == task_ids_to_complete[i] && !task.second.task().completed()) {
                task_ids_to_complete.push_back(task.first);
            }
        }
        auto completing_task = tasks_.find(task_ids_to_complete[i]);
        completing_task->second.mutable_task()->set_completed(true);
    }
    return TaskActionResult::SUCCESS;
}

std::vector<RelationalTask> TaskManager::GetTasks() {
    std::vector<RelationalTask> tasks;

    {
        std::lock_guard<std::mutex> guard(tasks_map_mutex_);

        std::transform(tasks_.begin(), tasks_.end(), std::back_inserter(tasks),
                       [this](const std::pair<TaskId, model::TaskNode> &task) {
                           return this->CreateRelationalTask(task.first, task.second);
                       });

    }

    LOG_TRIVIAL(debug) << "Tasks returned: " << tasks.size();

    return tasks;
}

std::optional<RelationalTask> TaskManager::GetTask(const TaskId& task_id) {
    std::lock_guard<std::mutex> guard(tasks_map_mutex_);

    auto task = tasks_.find(task_id);
    if (task == tasks_.end())
        return std::nullopt;

    return CreateRelationalTask(task->first, task->second);
}

TaskActionResult TaskManager::AddTaskLabel(const TaskId& id, const std::string& label) {
    if (label.empty())
        return TaskActionResult::SUCCESS;

    std::lock_guard<std::mutex> guard(tasks_map_mutex_);

    auto task_to_add_label = tasks_.find(id);
    if (task_to_add_label == tasks_.end())
        return TaskActionResult::FAIL_NO_SUCH_TASK;

    Task task = task_to_add_label->second.task();
    if (FindTaskLabel(task, label) != task.label().end())
        return TaskActionResult::SUCCESS;

    task.add_label(label);
    task_to_add_label->second.set_allocated_task(new Task(task));
    return TaskActionResult::SUCCESS;
}

TaskActionResult TaskManager::RemoveTaskLabel(const TaskId& id, const std::string& label) {
    std::lock_guard<std::mutex> guard(tasks_map_mutex_);

    auto task_to_remove_label = tasks_.find(id);
    if (task_to_remove_label == tasks_.end())
        return TaskActionResult::FAIL_NO_SUCH_TASK;

    Task task = task_to_remove_label->second.task();
    auto label_to_remove = FindTaskLabel(task, label);
    if (label_to_remove == task.label().end())
        return TaskActionResult::FAIL_NO_SUCH_LABEL;

    task.mutable_label()->erase(label_to_remove);
    task_to_remove_label->second.set_allocated_task(new Task(task));
    return TaskActionResult::SUCCESS;
}

google::protobuf::internal::RepeatedPtrIterator<const std::string> TaskManager::FindTaskLabel(const Task& task, const std::string& label) {
    return std::find_if(task.label().begin(), task.label().end(), [&label](const auto& task_label) {
        return task_label == label;
    });
}

bool TaskManager::LoadModelState(const std::vector<RelationalTask>& tasks) {
    std::lock_guard<std::mutex> guard(tasks_map_mutex_);

    std::map<TaskId, TaskNode> tasks_to_add;
    TaskId max_id;
    max_id.set_id(1);
    for (const auto& task : tasks) {
        if (!task.has_task() || !task.has_task_id() || !task_validator_->ValidateTask(task.task())) {
            return false;
        }
        if (task.task_id().id() > max_id.id())
            max_id = task.task_id();

        tasks_to_add.insert_or_assign(task.task_id(), model::CreateTaskNode(task));
    }
    generator_->SetLastTaskId(max_id);
    tasks_.swap(tasks_to_add);
    return true;
}

RelationalTask TaskManager::CreateRelationalTask(const TaskId& id, const TaskNode& task_node) {
    RelationalTask task;
    task.set_allocated_task_id(new TaskId(id));
    task.set_allocated_task(new Task(task_node.task()));
    if (task_node.has_parent_id())
        task.set_allocated_parent_id(new TaskId(task_node.parent_id()));

    return task;
}

std::vector<RelationalTask> TaskManager::GetTasksByLabel(const std::string& task_label) {
    std::lock_guard<std::mutex> guard(tasks_map_mutex_);

    std::vector<RelationalTask> tasks;
    for (const auto& rel_task : tasks_) {
        const auto task_labels = rel_task.second.task().label();
        if (std::find(task_labels.begin(), task_labels.end(), task_label) != task_labels.end()) {
            tasks.push_back(CreateRelationalTask(rel_task.first, rel_task.second));
        }
    }
    return tasks;
}
