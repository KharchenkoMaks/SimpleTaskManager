//
// Created by Maksym Kharchenko on 03.12.2021.
//

#ifndef SIMPLETASKMANAGER_MOCKMODEL_H
#define SIMPLETASKMANAGER_MOCKMODEL_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "abstract_model/IModel.h"

class MockModel : public IModel {
public:
    MOCK_METHOD(std::optional<TaskId>, AddTask, (const Task& t), (override));
    MOCK_METHOD(std::optional<TaskId>, AddSubTask, (const Task& task, const TaskId& parent_id), (override));
    MOCK_METHOD(bool, EditTask, (const TaskId& id, const Task& t), (override));
    MOCK_METHOD(bool, DeleteTask, (const TaskId& id), (override));
    MOCK_METHOD(bool, CompleteTask, (const TaskId& id), (override));
    MOCK_METHOD(std::vector<TaskTransfer>, GetTasks, (), (override));
    MOCK_METHOD(std::optional<TaskTransfer>, GetTask, (const TaskId& task_id), (override));
    MOCK_METHOD(bool, IsTaskIdExist, (const TaskId& task_id), (override));
};

#endif //SIMPLETASKMANAGER_MOCKMODEL_H
