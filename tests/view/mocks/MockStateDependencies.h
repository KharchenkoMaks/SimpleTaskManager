//
// Created by Maksym Kharchenko on 13.12.2021.
//

#ifndef SIMPLETASKMANAGER_MOCKSTATEDEPENDENCIES_H
#define SIMPLETASKMANAGER_MOCKSTATEDEPENDENCIES_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "states/abstract/StateDependencies.h"
#include "ConsoleStateMachine.h"

class MockStateDependencies : public StateDependencies {
public:
    MockStateDependencies() : StateDependencies(std::unique_ptr<ConsoleStateMachine>(nullptr), nullptr, nullptr, nullptr, nullptr) {}
public:
    MOCK_METHOD(std::shared_ptr<StatesFactory>, GetStatesFactory, (), (override));
    MOCK_METHOD(std::shared_ptr<Controller>, GetController, (), (override));
    MOCK_METHOD(std::shared_ptr<ConsolePrinter>, GetConsolePrinter, (), (override));

    MOCK_METHOD(std::string, GetUserInput, (const std::string &invitation_message), (override));
    MOCK_METHOD(bool, UserConfirm, (const std::string& question_string), (override));
    MOCK_METHOD(std::optional<TaskId>, GetTaskIdFromUser, (const std::string& invitation_string), (override));
    MOCK_METHOD(std::shared_ptr<StateContext>, RunStateMachine, (const std::shared_ptr<WizardContext>& context, const std::shared_ptr<WizardStateInterface>& initial_state), (override));
};

#endif //SIMPLETASKMANAGER_MOCKSTATEDEPENDENCIES_H
