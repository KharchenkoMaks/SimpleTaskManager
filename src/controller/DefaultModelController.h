//
// Created by Maksym Kharchenko on 24.01.2022.
//

#ifndef SIMPLETASKMANAGER_DEFAULTMODELCONTROLLER_H
#define SIMPLETASKMANAGER_DEFAULTMODELCONTROLLER_H

#include "ModelController.h"

#include "Model.h"
#include "utilities/TaskValidator.h"
#include "utilities/TaskActionResult.h"
#include "utilities/SaveLoadStatus.h"
#include "persistence/PersistenceFactory.h"

class DefaultModelController : public ModelController {
public:
    DefaultModelController(std::unique_ptr<Model> model,
                           std::unique_ptr<TaskValidator> task_validator,
                           std::unique_ptr<persistence::PersistenceFactory> persistence_factory);
public:
    std::pair<ControllerRequestResult, TaskId> AddTask(const Task& task) override;
    std::pair<ControllerRequestResult, TaskId> AddSubTask(const Task& task, const TaskId& parent_id) override;
    ControllerRequestResult EditTask(const TaskId& task_id, const Task& task) override;
    ControllerRequestResult DeleteTask(const TaskId& task_id) override;
    ControllerRequestResult CompleteTask(const TaskId& task_id) override;
    ControllerRequestResult AddTaskLabel(const TaskId& task_id, const std::string& label) override;
    ControllerRequestResult RemoveTaskLabel(const TaskId& task_id, const std::string& label) override;

    ControllerRequestResult DeleteTaskWithSubTasks(const TaskId& task_id) override;
    ControllerRequestResult CompleteTaskWithSubTasks(const TaskId& task_id) override;

public:
    std::vector<RelationalTask> GetAllTasks() override;
    std::vector<RelationalTask> GetTasksByLabel(const std::string& task_label) override;
    std::optional<RelationalTask> GetTask(const TaskId& task_id) override;
public:
    ControllerRequestResult SaveToFile(const std::string& file_name) override;
    ControllerRequestResult LoadFromFile(const std::string& file_name) override;

private:
    std::unique_ptr<Model> model_;
    std::unique_ptr<TaskValidator> task_validator_;
    std::unique_ptr<persistence::PersistenceFactory> persistence_factory_;
};


#endif //SIMPLETASKMANAGER_DEFAULTMODELCONTROLLER_H
