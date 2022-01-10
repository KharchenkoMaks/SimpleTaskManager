//
// Created by Maksym Kharchenko on 10.01.2022.
//

#ifndef SIMPLETASKMANAGER_MOCKCOMMANDFACTORY_H
#define SIMPLETASKMANAGER_MOCKCOMMANDFACTORY_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "view/commands/factory/CommandFactory.h"

class MockCommandFactory : public CommandFactory {
public:
    MOCK_METHOD(std::unique_ptr<CommandInterface>, CreateAddTaskCommand, (const StateContext& context), (override));
    MOCK_METHOD(std::unique_ptr<CommandInterface>, CreateAddSubTaskCommand, (const StateContext& context), (override));
    MOCK_METHOD(std::unique_ptr<CommandInterface>, CreateEditCommand, (const StateContext& context), (override));
    MOCK_METHOD(std::unique_ptr<CommandInterface>, CreateCompleteCommand, (const StateContext& context, bool force_complete_subtasks), (override));
    MOCK_METHOD(std::unique_ptr<CommandInterface>, CreateDeleteCommand, (const StateContext& context, bool force_delete_subtasks), (override));
    MOCK_METHOD(std::unique_ptr<CommandInterface>, CreateSetLabelCommand, (const StateContext& context), (override));
    MOCK_METHOD(std::unique_ptr<CommandInterface>, CreateShowCommand, (const StateContext& context), (override));
    MOCK_METHOD(std::unique_ptr<CommandInterface>, CreateSaveCommand, (const StateContext& context), (override));
    MOCK_METHOD(std::unique_ptr<CommandInterface>, CreateLoadCommand, (const StateContext& context), (override));
};

#endif //SIMPLETASKMANAGER_MOCKCOMMANDFACTORY_H
