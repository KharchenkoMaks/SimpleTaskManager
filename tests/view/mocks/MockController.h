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
    MockController(std::unique_ptr<IModel> model, std::unique_ptr<TaskValidator> task_validator) : Controller(std::move(model), std::move(task_validator)) {}

    MOCK_METHOD(std::string, GetAllTasks, (), (override));
    MOCK_METHOD((std::pair<TaskActionResult, std::optional<TaskId>>), AddTask, (const Task& task), (override));
    MOCK_METHOD((std::pair<TaskActionResult, std::optional<TaskId>>), AddSubTask, (const Task& task, const TaskId& parent_id), (override));
};

#endif //SIMPLETASKMANAGER_MOCKCONTROLLER_H
