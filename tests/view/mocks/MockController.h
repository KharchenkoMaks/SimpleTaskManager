//
// Created by Maksym Kharchenko on 03.12.2021.
//

#ifndef SIMPLETASKMANAGER_MOCKCONTROLLER_H
#define SIMPLETASKMANAGER_MOCKCONTROLLER_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Controller.h"

#include "utilities/TaskActionResult.h"
#include "utilities/SaveLoadStatus.h"

#include <utility>

class MockController : public Controller {
public:
    MockController() : Controller(nullptr, nullptr, nullptr) {}

    MOCK_METHOD((std::pair<ControllerRequestResult, TaskId>), AddTask, (const Task& task), (override));
    MOCK_METHOD((std::pair<ControllerRequestResult, TaskId>), AddSubTask, (const Task& task, const TaskId& parent_id), (override));
    MOCK_METHOD(ControllerRequestResult, EditTask, (const TaskId& task_id, const Task& task), (override));
    MOCK_METHOD(ControllerRequestResult, DeleteTask, (const TaskId& task_id), (override));
    MOCK_METHOD(ControllerRequestResult, CompleteTask, (const TaskId& task_id), (override));
    MOCK_METHOD(ControllerRequestResult, SetTaskLabel, (const TaskId& task_id, const std::string& label), (override));
    MOCK_METHOD(ControllerRequestResult, DeleteTaskWithSubTasks, (const TaskId& task_id), (override));
    MOCK_METHOD(ControllerRequestResult, CompleteTaskWithSubTasks, (const TaskId& task_id), (override));
    MOCK_METHOD(std::vector<TaskTransfer>, GetAllTasks, (), (override));
    MOCK_METHOD(std::optional<TaskTransfer>, GetTask, (const TaskId& task_id), (override));
    MOCK_METHOD(ControllerRequestResult, SaveToFile, (const std::string& file_name), (override));
    MOCK_METHOD(ControllerRequestResult, LoadFromFile, (const std::string& file_name), (override));
};

#endif //SIMPLETASKMANAGER_MOCKCONTROLLER_H
