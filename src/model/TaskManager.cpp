//
// Created by Maksym Kharchenko on 08.11.2021.
//

#include "TaskManager.h"
#include "utilities/TaskComparators.h"
#include "TaskNodeFactoryMethod.h"

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
        return std::pair(TaskActionResult::FAIL_INVALID_TASK, TaskId::default_instance());
    }

    TaskId task_id = generator_->CreateNewTaskId();
    tasks_.insert({ task_id, model::CreateTaskNode(task) });
    return std::pair(TaskActionResult::SUCCESS, task_id);
}

std::pair<TaskActionResult, TaskId> TaskManager::AddSubTask(const Task& task, const TaskId& parent_id) {
    if (!task_validator_->ValidateTask(task)) {
        return std::pair(TaskActionResult::FAIL_INVALID_TASK, TaskId::default_instance());
    }

    auto parent_task = tasks_.find(parent_id);
    if (parent_task == tasks_.end()) {
        return std::pair(TaskActionResult::FAIL_NO_SUCH_TASK, TaskId::default_instance());
    }

    TaskId subtask_id = generator_->CreateNewTaskId();
    tasks_.insert({ subtask_id, model::CreateTaskNode(task, parent_id) });
    return std::pair(TaskActionResult::SUCCESS, subtask_id);
}

TaskActionResult TaskManager::EditTask(const TaskId& id, const Task& task) {
    if (!task_validator_->ValidateTask(task)) {
        return TaskActionResult::FAIL_INVALID_TASK;
    }

    auto editing_task = tasks_.find(id);
    if (editing_task == tasks_.end())
        return TaskActionResult::FAIL_NO_SUCH_TASK;

    editing_task->second.set_allocated_task(new Task(task));
    return TaskActionResult::SUCCESS;
}

TaskActionResult TaskManager::DeleteTask(const TaskId& id, bool force_delete_subtasks) {
    auto deleting_task = tasks_.find(id);
    if (deleting_task == tasks_.end())
        return TaskActionResult::FAIL_NO_SUCH_TASK;

    auto search_child_rule = [&id](const std::pair<TaskId, TaskNode>& task) {
        return task.second.parent_id() == id;
    };
    if (force_delete_subtasks) {
        auto subtask = std::find_if(tasks_.begin(), tasks_.end(), search_child_rule);
        while (subtask != tasks_.end()) {
            this->DeleteTask(subtask->first, true);
            subtask = std::find_if(tasks_.begin(), tasks_.end(), search_child_rule);
        }
    } else if (std::find_if(tasks_.begin(), tasks_.end(), search_child_rule) != tasks_.end()) {
        return TaskActionResult::FAIL_NOT_DELETED_SUBTASKS;
    }

    deleted_tasks_.insert_or_assign(deleting_task->first, deleting_task->second);
    tasks_.erase(deleting_task);
    return TaskActionResult::SUCCESS;
}

TaskActionResult TaskManager::CompleteTask(const TaskId& id, bool force_complete_subtasks) {
    auto completing_task = tasks_.find(id);
    if (completing_task == tasks_.end())
        return TaskActionResult::FAIL_NO_SUCH_TASK;

    auto search_uncompleted_child_rule = [&id](const std::pair<TaskId, TaskNode>& task) {
        return task.second.parent_id() == id && !task.second.task().completed();
    };

    if (force_complete_subtasks) {
        for (const auto& task : tasks_)
            if (task.second.parent_id() == id && !task.second.task().completed())
                this->CompleteTask(task.first, true);
    } else if (std::find_if(tasks_.begin(), tasks_.end(), search_uncompleted_child_rule) != tasks_.end()) {
        return TaskActionResult::FAIL_UNCOMPLETED_SUBTASKS;
    }

    Task task_to_complete = completing_task->second.task();
    task_to_complete.set_completed(true);
    completing_task->second.set_allocated_task(new Task(task_to_complete));
    return TaskActionResult::SUCCESS;
}

std::vector<RelationalTask> TaskManager::GetTasks() {
    std::vector<RelationalTask> tasks;
    for (const auto& task : tasks_) {
        if (!task.second.has_parent_id()) {
            auto adding_tasks = GetAllTaskChildren(task.first);
            tasks.insert(tasks.end(), adding_tasks.begin(), adding_tasks.end());
        }
    }
    return tasks;
}

bool TaskManager::IsTaskExist(const TaskId& task_id) {
    return tasks_.find(task_id) != tasks_.end();
}

std::optional<RelationalTask> TaskManager::GetTask(const TaskId& task_id) {
    auto task = tasks_.find(task_id);
    if (task == tasks_.end())
        return std::nullopt;

    return CreateTaskTransferFromTask(task);
}

TaskActionResult TaskManager::AddTaskLabel(const TaskId& id, const std::string& label) {
    if (label.empty())
        return TaskActionResult::SUCCESS;

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

std::vector<RelationalTask> TaskManager::GetAllTaskChildren(const TaskId& task_id) {
    std::vector<RelationalTask> tasks;
    auto main_task = tasks_.find(task_id);
    if (main_task == tasks_.end())
        return tasks;

    tasks.push_back(CreateTaskTransferFromTask(main_task));
    for (const auto& task : tasks_) {
        if (task.second.parent_id() == task_id) {
            auto task_children = GetAllTaskChildren(task.first);
            tasks.insert(tasks.end(), task_children.begin(), task_children.end());
        }
    }

    return tasks;
}

RelationalTask TaskManager::CreateTaskTransferFromTask(const std::map<TaskId, TaskNode>::iterator& task) {
    RelationalTask task_transfer;
    task_transfer.set_allocated_task_id(new TaskId(task->first));
    task_transfer.set_allocated_task(new Task(task->second.task()));
    if (task->second.has_parent_id()) {
        task_transfer.set_allocated_parent_id(new TaskId(task->second.parent_id()));
    }
    return task_transfer;
}
