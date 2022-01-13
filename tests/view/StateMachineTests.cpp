//
// Created by Maksym Kharchenko on 13.01.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Task.pb.h"

#include "view/user_interface/ConsoleStateMachine.h"

#include "mocks/MockState.h"

using ::testing::Return;

class StateMachineTests : public ::testing::Test {

};

TEST_F(StateMachineTests, Run_ShouldStartWithInitialStateAndReturnContextAtTheEnd) {
    // Arrange
    std::shared_ptr<StateContext> context = std::make_shared<StateContext>();
    std::shared_ptr<MockState> initial_state = std::make_shared<MockState>();
    std::shared_ptr<MockState> second_state = std::make_shared<MockState>();
    EXPECT_CALL(*initial_state, Execute(testing::Ref(*context)))
        .WillOnce(Return(second_state));
    EXPECT_CALL(*second_state, Execute(testing::Ref(*context)))
        .WillOnce(Return(nullptr));
    ConsoleStateMachine state_machine;
    // Act
    std::shared_ptr<StateContext> actual_returned_context = state_machine.Run(context, initial_state);
    // Assert
    EXPECT_EQ(context, actual_returned_context);
}