//
// Created by Maksym Kharchenko on 29.11.2021.
//

#ifndef SIMPLETASKMANAGER_CONTROLLER_H
#define SIMPLETASKMANAGER_CONTROLLER_H

#include "TaskId.h"
#include "tasks/Task.h"
#include "TaskManager.h"
#include "TaskValidator.h"

#include <memory>

class Controller {
public:
    Controller(std::unique_ptr<TaskManager> task_manager, std::unique_ptr<TaskValidator> task_validator);
public:
    TaskId AddTask(const Task& task);
    void EditTask(const TaskId& task_id, const Task& task);
    void DeleteTask(const TaskId& task_id);
    void CompleteTask(const TaskId& task_id);

    std::string GetAllTasks();
public:
    std::optional<Task> GetTask(const TaskId& task_id) const;
private:
    std::unique_ptr<TaskManager> task_manager_;

    std::unique_ptr<TaskValidator> task_validator_;
};


#endif //SIMPLETASKMANAGER_CONTROLLER_H
