//
// Created by Maksym Kharchenko on 03.12.2021.
//

#ifndef SIMPLETASKMANAGER_MOCKCONTROLLER_H
#define SIMPLETASKMANAGER_MOCKCONTROLLER_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Controller.h"

class MockController : public Controller {
public:
    MockController(std::unique_ptr<IModel> model, std::unique_ptr<TaskValidator> task_validator) : Controller(std::move(model), std::move(task_validator)) {}

    MOCK_METHOD(std::string, GetAllTasks, (), (override));
    MOCK_METHOD(std::optional<TaskId>, AddTask, (const Task& task), (override))

    std::pair<TaskActionResult, std::optional<TaskId>>

    ;
    MOCK_METHOD(std::optional<TaskId>, AddSubTask, (const Task& task, const TaskId& parent_id), (override))

    std::pair<TaskActionResult, std::optional<TaskId>>

    ;
};

#endif //SIMPLETASKMANAGER_MOCKCONTROLLER_H
