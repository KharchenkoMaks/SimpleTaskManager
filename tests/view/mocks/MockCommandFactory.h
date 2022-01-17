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
    MOCK_METHOD(std::unique_ptr<Command>, CreateAddTaskCommand, (const StateContext& context), (override));
    MOCK_METHOD(std::unique_ptr<Command>, CreateAddSubTaskCommand, (const StateContext& context), (override));
    MOCK_METHOD(std::unique_ptr<Command>, CreateEditCommand, (const StateContext& context), (override));
    MOCK_METHOD(std::unique_ptr<Command>, CreateCompleteCommand, (const StateContext& context, bool force_complete_subtasks), (override));
    MOCK_METHOD(std::unique_ptr<Command>, CreateDeleteCommand, (const StateContext& context, bool force_delete_subtasks), (override));
    MOCK_METHOD(std::unique_ptr<Command>, CreateSetLabelCommand, (const StateContext& context), (override));
    MOCK_METHOD(std::unique_ptr<Command>, CreateRemoveLabelCommand, (const StateContext& context), (override));
    MOCK_METHOD(std::unique_ptr<Command>, CreateShowCommand, (const StateContext& context), (override));
    MOCK_METHOD(std::unique_ptr<Command>, CreateSaveCommand, (const StateContext& context), (override));
    MOCK_METHOD(std::unique_ptr<Command>, CreateLoadCommand, (const StateContext& context), (override));
};

#endif //SIMPLETASKMANAGER_MOCKCOMMANDFACTORY_H
