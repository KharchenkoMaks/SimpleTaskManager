//
// Created by Maksym Kharchenko on 03.12.2021.
//

#ifndef SIMPLETASKMANAGER_MOCKWIZARDSTATESFACTORY_H
#define SIMPLETASKMANAGER_MOCKWIZARDSTATESFACTORY_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "states/factory/WizardStatesFactory.h"
#include "Controller.h"

class MockWizardStatesFactory : public WizardStatesFactory {
public:
    MockWizardStatesFactory() : WizardStatesFactory(nullptr, nullptr, nullptr) {}

    MOCK_METHOD(std::shared_ptr<WizardStateInterface>, GetNextState, (const QuitState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<WizardStateInterface>, GetNextState, (const RootState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<WizardStateInterface>, GetNextState, (const ShowState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<WizardStateInterface>, GetNextState, (const HelpState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<WizardStateInterface>, GetNextState, (const AddTaskState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<WizardStateInterface>, GetNextState, (const InputTaskTitleState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<WizardStateInterface>, GetNextState, (const InputTaskPriorityState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<WizardStateInterface>, GetNextState, (const InputTaskDueDateState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<WizardStateInterface>, GetNextState, (const AddSubTaskState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<WizardStateInterface>, GetNextState, (const DeleteTaskState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<WizardStateInterface>, GetNextState, (const SaveState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<WizardStateInterface>, GetNextState, (const LoadState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<WizardStateInterface>, GetStateByCommand, (const std::string& command), (override));
};

#endif //SIMPLETASKMANAGER_MOCKWIZARDSTATESFACTORY_H
