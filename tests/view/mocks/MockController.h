//
// Created by Maksym Kharchenko on 03.12.2021.
//

#ifndef SIMPLETASKMANAGER_MOCKCONTROLLER_H
#define SIMPLETASKMANAGER_MOCKCONTROLLER_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Controller.h"

#include "utilities/TaskActionResult.h"

#include <utility>

class MockController : public Controller {
public:
    MockController() : Controller(nullptr, nullptr) {}

    MOCK_METHOD(std::vector<TaskTransfer>, GetAllTasks, (), (override));
    MOCK_METHOD((std::pair<TaskActionResult, std::optional<TaskId>>), AddTask, (const Task& task), (override));
    MOCK_METHOD((std::pair<TaskActionResult, std::optional<TaskId>>), AddSubTask, (const Task& task, const TaskId& parent_id), (override));
    MOCK_METHOD(TaskActionResult, DeleteTask, (const TaskId& task_id), (override));
    MOCK_METHOD(TaskManagerPersistence::SaveLoadStatus, SaveToFile, (const std::string& file_name), (override));
    MOCK_METHOD(TaskManagerPersistence::SaveLoadStatus, LoadFromFile, (const std::string& file_name), (override));
};

#endif //SIMPLETASKMANAGER_MOCKCONTROLLER_H
