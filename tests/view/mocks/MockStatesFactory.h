//
// Created by Maksym Kharchenko on 03.12.2021.
//

#ifndef SIMPLETASKMANAGER_MOCKSTATESFACTORY_H
#define SIMPLETASKMANAGER_MOCKSTATESFACTORY_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "states/factory/StatesFactory.h"
#include "Controller.h"

class MockStatesFactory : public StatesFactory {
public:
    MockStatesFactory() : StatesFactory(nullptr, nullptr, nullptr) {}

    MOCK_METHOD(std::shared_ptr<StateInterface>, GetNextState, (const QuitState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<StateInterface>, GetNextState, (const RootState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<StateInterface>, GetNextState, (const ShowState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<StateInterface>, GetNextState, (const HelpState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<StateInterface>, GetNextState, (const AddTaskState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<StateInterface>, GetNextState, (const InputTaskTitleState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<StateInterface>, GetNextState, (const InputTaskPriorityState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<StateInterface>, GetNextState, (const InputTaskDueDateState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<StateInterface>, GetNextState, (const AddSubTaskState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<StateInterface>, GetNextState, (const DeleteTaskState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<StateInterface>, GetNextState, (const SaveState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<StateInterface>, GetNextState, (const LoadState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<StateInterface>, GetNextState, (const EditTaskState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<StateInterface>, GetNextState, (const SetLabelState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<StateInterface>, GetNextState, (const CompleteTaskState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<StateInterface>, GetNextState, (const InputShowParametersState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<StateInterface>, GetRootState, (), (override));
    MOCK_METHOD(std::shared_ptr<StateInterface>, GetShowState, (), (override));
    MOCK_METHOD(std::shared_ptr<StateInterface>, GetStateByCommand, (const std::string& command), (override));
    MOCK_METHOD(std::shared_ptr<ConsolePrinter>, GetConsolePrinter, (), (const, override));
    MOCK_METHOD(std::shared_ptr<ConsoleReader>, GetConsoleReader, (), (const, override));
    MOCK_METHOD(std::shared_ptr<CommandFactory>, GetCommandFactory, (), (const, override));
    MOCK_METHOD(std::unique_ptr<ConsoleStateMachine>, CreateStateMachine, (), (const, override));
};

#endif //SIMPLETASKMANAGER_MOCKSTATESFACTORY_H
