//
// Created by Maksym Kharchenko on 03.12.2021.
//

#ifndef SIMPLETASKMANAGER_MOCKSTATESFACTORY_H
#define SIMPLETASKMANAGER_MOCKSTATESFACTORY_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "states/factory/StatesFactory.h"
#include "ModelController.h"

class MockStatesFactory : public StatesFactory {
public:
    MockStatesFactory() : StatesFactory(nullptr, nullptr, nullptr) {}

    MOCK_METHOD(std::shared_ptr<State>, GetNextState, (const QuitState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<State>, GetNextState, (const RootState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<State>, GetNextState, (const ShowState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<State>, GetNextState, (const HelpState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<State>, GetNextState, (const AddTaskState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<State>, GetNextState, (const InputTaskTitleState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<State>, GetNextState, (const InputTaskPriorityState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<State>, GetNextState, (const InputTaskDueDateState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<State>, GetNextState, (const AddSubTaskState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<State>, GetNextState, (const DeleteTaskState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<State>, GetNextState, (const SaveState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<State>, GetNextState, (const LoadState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<State>, GetNextState, (const EditTaskState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<State>, GetNextState, (const SetLabelState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<State>, GetNextState, (const RemoveLabelState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<State>, GetNextState, (const CompleteTaskState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<State>, GetNextState, (const InputShowParametersState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<State>, GetNextState, (const InputShowByLabelState& state, MoveType move_type), (override));
    MOCK_METHOD(std::shared_ptr<State>, GetRootState, (), (override));
    MOCK_METHOD(std::shared_ptr<State>, GetShowState, (), (override));
    MOCK_METHOD(std::shared_ptr<State>, GetStateByCommand, (const std::string& command), (override));
    MOCK_METHOD(std::shared_ptr<ConsolePrinter>, GetConsolePrinter, (), (const, override));
    MOCK_METHOD(std::shared_ptr<ConsoleReader>, GetConsoleReader, (), (const, override));
    MOCK_METHOD(std::shared_ptr<CommandFactory>, GetCommandFactory, (), (const, override));
    MOCK_METHOD(std::shared_ptr<State>, GetInputShowParametersInitialState, (), (override));
    MOCK_METHOD(std::unique_ptr<ConsoleStateMachine>, CreateStateMachine, (const std::shared_ptr<State>& initial_state, const std::shared_ptr<StateContext>& context), (const, override));
};

#endif //SIMPLETASKMANAGER_MOCKSTATESFACTORY_H
