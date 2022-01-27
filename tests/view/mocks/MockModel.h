//
// Created by Maksym Kharchenko on 03.12.2021.
//

#ifndef SIMPLETASKMANAGER_MOCKMODEL_H
#define SIMPLETASKMANAGER_MOCKMODEL_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Model.h"
#include "utilities/TaskActionResult.h"

class MockModel : public Model {
public:
    MOCK_METHOD((std::pair<TaskActionResult, TaskId>), AddTask, (const Task& t), (override));
    MOCK_METHOD((std::pair<TaskActionResult, TaskId>), AddSubTask, (const Task& task, const TaskId& parent_id), (override));
    MOCK_METHOD(TaskActionResult, EditTask, (const TaskId& id, const Task& t), (override));
    MOCK_METHOD(TaskActionResult, DeleteTask, (const TaskId& id, bool force_delete_subtasks), (override));
    MOCK_METHOD(TaskActionResult, CompleteTask, (const TaskId& id, bool force_complete_subtasks), (override));
    MOCK_METHOD(std::vector<RelationalTask>, GetTasks, (), (override));
    MOCK_METHOD(std::optional<RelationalTask>, GetTask, (const TaskId& task_id), (override));
    MOCK_METHOD(TaskActionResult, AddTaskLabel, (const TaskId& id, const std::string& label), (override));
    MOCK_METHOD(bool, LoadModelState, (const std::vector<RelationalTask>& tasks), (override));
    MOCK_METHOD(TaskActionResult, RemoveTaskLabel, (const TaskId& id, const std::string& label), (override));
};

#endif //SIMPLETASKMANAGER_MOCKMODEL_H
