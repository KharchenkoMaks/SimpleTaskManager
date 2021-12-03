//
// Created by Maksym Kharchenko on 03.12.2021.
//

#ifndef SIMPLETASKMANAGER_MOCKTASKVALIDATOR_H
#define SIMPLETASKMANAGER_MOCKTASKVALIDATOR_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "TaskValidator.h"

class MockTaskValidator : public TaskValidator {
public:
    MOCK_METHOD(bool, ValidateTask, (const Task& task), (override));
    MOCK_METHOD(bool, ValidateTaskId, (const TaskId& task_id, (override)));
};

#endif //SIMPLETASKMANAGER_MOCKTASKVALIDATOR_H
