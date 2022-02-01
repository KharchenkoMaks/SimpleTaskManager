//
// Created by Maksym Kharchenko on 13.01.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "view/user_interface/ConsoleStateMachine.h"

#include "mocks/MockState.h"
#include "mocks/MockStatesFactory.h"

using ::testing::Return;

class StateMachineTests : public ::testing::Test {

};

TEST_F(StateMachineTests, Run_ShouldStartWithInitialStateAndReturnContextAtTheEnd) {
    // Arrange
    const auto initial_state_type = StateType::kRoot;
    const auto second_state_type = StateType::kShow;
    auto initial_state = std::make_shared<MockState>();
    auto second_state = std::make_shared<MockState>();

    auto context = std::make_unique<StateContext>();
    auto states_factory = std::make_shared<MockStatesFactory>();

    const int testing_times = 2;

    for (int i = 0; i < testing_times; ++i) {
        EXPECT_CALL(*states_factory, GetState(initial_state_type)).WillOnce(Return(initial_state));
        EXPECT_CALL(*states_factory, GetState(second_state_type)).WillOnce(Return(second_state));
        EXPECT_CALL(*initial_state, Execute(::testing::_)).WillOnce(Return(second_state_type));
        EXPECT_CALL(*second_state, Execute(::testing::_)).WillOnce(Return(StateType::kEnd));
    }
    ConsoleStateMachine state_machine { initial_state_type, std::move(context), states_factory };
    // Act
    std::vector<std::shared_ptr<StateContext>> actual_result_contexts;
    for (int i = 0; i < testing_times; ++i)
        actual_result_contexts.push_back(state_machine.Run());
    // Assert
    for (int i = 0; i < testing_times; ++i) {
        for (int j = i + 1; j < testing_times; ++j) {
            EXPECT_NE(actual_result_contexts[i], actual_result_contexts[j]);
        }
    }
}