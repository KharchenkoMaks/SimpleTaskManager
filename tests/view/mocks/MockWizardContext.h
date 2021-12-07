//
// Created by Maksym Kharchenko on 06.12.2021.
//

#ifndef SIMPLETASKMANAGER_MOCKWIZARDCONTEXT_H
#define SIMPLETASKMANAGER_MOCKWIZARDCONTEXT_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "WizardContext.h"

#include <string>

class MockWizardContext : public WizardContext {
public:
    MOCK_METHOD(bool, AddTaskTitle, (const std::string& title), (override));
    MOCK_METHOD(bool, AddTaskPriority, (Task::Priority priority), (override));
    MOCK_METHOD(bool, AddTaskDueTime, (DueTime due_time), (override));
    MOCK_METHOD(std::optional<Task>, GetTask, (), (override));
    MOCK_METHOD(void, SetEditingTask, (const TaskId& task_id, const Task& task), (override));
    MOCK_METHOD(std::optional<TaskId>, GetTaskId, (), (override));
};

#endif //SIMPLETASKMANAGER_MOCKWIZARDCONTEXT_H
