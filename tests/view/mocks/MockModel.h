//
// Created by Maksym Kharchenko on 03.12.2021.
//

#ifndef SIMPLETASKMANAGER_MOCKMODEL_H
#define SIMPLETASKMANAGER_MOCKMODEL_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "abstract_model/IModel.h"
#include "utilities/TaskActionResult.h"

class MockModel : public IModel {
public:
    MOCK_METHOD((std::pair<TaskActionResult, std::optional<TaskId>>), AddTask, (const Task& t), (override));
    MOCK_METHOD((std::pair<TaskActionResult, std::optional<TaskId>>), AddSubTask, (const Task& task, const TaskId& parent_id), (override));
    MOCK_METHOD(TaskActionResult, EditTask, (const TaskId& id, const Task& t), (override));
    MOCK_METHOD(TaskActionResult, DeleteTask, (const TaskId& id, bool force_delete_subtasks), (override));
    MOCK_METHOD(TaskActionResult, CompleteTask, (const TaskId& id, bool force_complete_subtasks), (override));
    MOCK_METHOD(std::vector<TaskTransfer>, GetTasks, (), (override));
    MOCK_METHOD(std::optional<TaskTransfer>, GetTask, (const TaskId& task_id), (override));
    MOCK_METHOD(bool, IsTaskExist, (const TaskId& task_id), (override));
    MOCK_METHOD((std::pair<TaskActionResult, std::vector<TaskTransfer>>), GetTaskSubTasks, (const TaskId& task_id), (override));
    MOCK_METHOD(TaskActionResult, SetTaskLabel, (const TaskId& id, const std::string& label), (override));
    MOCK_METHOD((std::pair<TaskId, std::vector<TaskTransfer>>), GetModelState, (), (override));
    MOCK_METHOD(bool, LoadModelState, (std::unique_ptr<IdGenerator> generator, const std::vector<TaskTransfer>& tasks), (override));
};

#endif //SIMPLETASKMANAGER_MOCKMODEL_H
