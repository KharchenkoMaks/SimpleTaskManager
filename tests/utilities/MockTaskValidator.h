//
// Created by Maksym Kharchenko on 03.12.2021.
//

#ifndef SIMPLETASKMANAGER_MOCKTASKVALIDATOR_H
#define SIMPLETASKMANAGER_MOCKTASKVALIDATOR_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "utilities/TaskValidator.h"

class MockTaskValidator : public TaskValidator {
public:
    MOCK_METHOD(bool, ValidateTask, (const Task& task), (override));
};

#endif //SIMPLETASKMANAGER_MOCKTASKVALIDATOR_H
