//
// Created by Maksym Kharchenko on 10.01.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Task.pb.h"

#include "view/states/task_input/AddSubTaskState.h"
#include "view/states/task_input/InputTaskTitleState.h"
#include "view/states/EndState.h"

#include "mocks/MockStatesFactory.h"
#include "mocks/MockCommandFactory.h"
#include "mocks/MockConsolePrinter.h"
#include "mocks/MockConsoleReader.h"
#include "mocks/MockStateMachine.h"

#include "utilities/TaskComparators.h"

#include <ctime>
#include <google/protobuf/util/time_util.h>

using ::testing::Return;

class StatesTests : public ::testing::Test {
public:
    std::shared_ptr<MockStatesFactory> states_factory_;
    std::shared_ptr<MockConsolePrinter> console_printer_;
    std::shared_ptr<MockConsoleReader> console_reader_;
    std::shared_ptr<MockCommandFactory> command_factory_;

    std::unique_ptr<MockStateMachine> state_machine_;
    void SetUp() override {
        states_factory_ = std::make_shared<MockStatesFactory>();
        console_printer_ = std::make_shared<MockConsolePrinter>();
        console_reader_ = std::make_shared<MockConsoleReader>();
        command_factory_ = std::make_shared<MockCommandFactory>();
        state_machine_ = std::make_unique<MockStateMachine>();
        EXPECT_CALL(*states_factory_, GetConsolePrinter()).WillRepeatedly(Return(console_printer_));
        EXPECT_CALL(*states_factory_, GetConsoleReader()).WillRepeatedly(Return(console_reader_));
        EXPECT_CALL(*states_factory_, GetCommandFactory()).WillRepeatedly(Return(command_factory_));
        EXPECT_CALL(*states_factory_, CreateStateMachine()).WillRepeatedly(Return(testing::ByMove(std::move(state_machine_))));
    }
    void ExpectGetUserInput(const std::string& message, const std::string& returned_input) {
        EXPECT_CALL(*console_printer_, Write(message + "> ")).Times(1);
        EXPECT_CALL(*console_reader_, ReadLine()).WillOnce(Return(returned_input));
    }
    std::shared_ptr<StateContext> GetContextWithFilledTask() {
        std::shared_ptr<StateContext> context_with_task = std::make_shared<StateContext>();
        context_with_task->AddTaskTitle("Task title");
        context_with_task->AddTaskPriority(Task::Priority::Task_Priority_LOW);
        context_with_task->AddTaskDueTime(google::protobuf::Timestamp(google::protobuf::util::TimeUtil::TimeTToTimestamp(time(0))));
        context_with_task->AddTaskLabel("Task label");
        return context_with_task;
    }
};

TEST_F(StatesTests, AddSubTaskStateExecuteShouldCreateAddSubTaskCommand) {
    // Arrange
    std::shared_ptr<StateInterface> expected_state_machine_initial_state = std::make_shared<InputTaskTitleState>(nullptr);
    std::shared_ptr<StateInterface> expected_next_state = std::make_shared<EndState>(nullptr);
    std::shared_ptr<StateContext> expected_returned_context_from_state_machine = GetContextWithFilledTask();
    TaskId expected_parent_id;
    expected_parent_id.set_id(5);
    StateContext add_subtask_context;
    AddSubTaskState add_subtask_state(states_factory_);

    // Assert
    ExpectGetUserInput("Parent Task ID", "5");

    EXPECT_CALL(*states_factory_, GetNextState(testing::An<const AddSubTaskState&>(), StatesFactory::MoveType::NEXT))
        .WillOnce(Return(expected_state_machine_initial_state));
    EXPECT_CALL(*states_factory_, GetNextState(testing::An<const AddSubTaskState&>(), StatesFactory::MoveType::PREVIOUS))
            .WillOnce(Return(expected_next_state));

    std::unique_ptr<MockStateMachine> state_machine = std::make_unique<MockStateMachine>();
    EXPECT_CALL(*state_machine, Run(testing::_, expected_state_machine_initial_state))
            .WillOnce(Return(expected_returned_context_from_state_machine));
    EXPECT_CALL(*states_factory_, CreateStateMachine())
        .WillOnce(Return(testing::ByMove(std::move(state_machine))));

    EXPECT_CALL(*command_factory_, CreateAddSubTaskCommand(testing::_)).Times(1);
    // Act
    std::shared_ptr<StateInterface> actual_next_state = add_subtask_state.Execute(add_subtask_context);
    // Assert
    EXPECT_EQ(add_subtask_context.GetTaskBuilder().BuildTask(), expected_returned_context_from_state_machine->GetTaskBuilder().BuildTask());
    EXPECT_EQ(expected_next_state, actual_next_state);
}