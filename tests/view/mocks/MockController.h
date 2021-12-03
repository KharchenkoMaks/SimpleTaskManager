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


};

#endif //SIMPLETASKMANAGER_MOCKCONTROLLER_H
