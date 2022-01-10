//
// Created by Maksym Kharchenko on 10.01.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Task.pb.h"

#include "view/states/task_input/AddSubTaskState.h"
#include "view/states/task_input/AddTaskState.h"
#include "view/states/task_input/EditTaskState.h"
#include "view/states/task_input/InputTaskTitleState.h"
#include "view/states/task_input/InputTaskPriorityState.h"
#include "view/states/task_input/InputTaskDueDateState.h"
#include "view/states/RootState.h"
#include "view/states/EndState.h"

#include "mocks/MockStatesFactory.h"
#include "mocks/MockCommandFactory.h"
#include "mocks/MockConsolePrinter.h"
#include "mocks/MockConsoleReader.h"
#include "mocks/MockStateMachine.h"

#include "utilities/TaskConvertors.h"
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

    EXPECT_CALL(*command_factory_, CreateAddSubTaskCommand(testing::Ref(add_subtask_context))).Times(1);
    // Act
    std::shared_ptr<StateInterface> actual_next_state = add_subtask_state.Execute(add_subtask_context);
    // Assert
    EXPECT_EQ(add_subtask_context.GetTaskBuilder().BuildTask(), expected_returned_context_from_state_machine->GetTaskBuilder().BuildTask());
    EXPECT_EQ(expected_next_state, actual_next_state);
}

TEST_F(StatesTests, AddSubTaskStateExecuteGivenWrongParentId_ShouldReturnErrorNextState) {
    // Assert
    std::shared_ptr<StateInterface> expected_next_state = std::shared_ptr<RootState>(nullptr);
    StateContext add_subtask_context;
    AddSubTaskState add_subtask_state(states_factory_);
    // Assert
    ExpectGetUserInput("Parent Task ID", "qwe");

    EXPECT_CALL(*states_factory_, GetNextState(testing::An<const AddSubTaskState&>(), StatesFactory::MoveType::ERROR))
            .WillOnce(Return(expected_next_state));

    EXPECT_CALL(*console_printer_, WriteError("Incorrect task id was given, try again!")).Times(1);
    // Act
    std::shared_ptr<StateInterface> actual_next_state = add_subtask_state.Execute(add_subtask_context);
    // Assert
    EXPECT_EQ(expected_next_state, actual_next_state);
}

TEST_F(StatesTests, AddTaskExecuteShouldCreateAddTaskCommand) {
    std::shared_ptr<StateInterface> expected_state_machine_initial_state = std::make_shared<InputTaskTitleState>(nullptr);
    std::shared_ptr<StateInterface> expected_next_state = std::make_shared<EndState>(nullptr);
    std::shared_ptr<StateContext> expected_returned_context_from_state_machine = GetContextWithFilledTask();
    StateContext add_task_context;
    AddTaskState add_task_state(states_factory_);
    // Assert
    EXPECT_CALL(*states_factory_, GetNextState(testing::An<const AddTaskState&>(), StatesFactory::MoveType::NEXT))
            .WillOnce(Return(expected_state_machine_initial_state));
    EXPECT_CALL(*states_factory_, GetNextState(testing::An<const AddTaskState&>(), StatesFactory::MoveType::PREVIOUS))
            .WillOnce(Return(expected_next_state));
    std::unique_ptr<MockStateMachine> state_machine = std::make_unique<MockStateMachine>();
    EXPECT_CALL(*state_machine, Run(testing::_, expected_state_machine_initial_state))
            .WillOnce(Return(expected_returned_context_from_state_machine));
    EXPECT_CALL(*states_factory_, CreateStateMachine())
            .WillOnce(Return(testing::ByMove(std::move(state_machine))));

    EXPECT_CALL(*command_factory_, CreateAddTaskCommand(testing::Ref(add_task_context))).Times(1);
    // Act
    std::shared_ptr<StateInterface> actual_next_state = add_task_state.Execute(add_task_context);
    // Assert
    EXPECT_EQ(add_task_context.GetTaskBuilder().BuildTask(), expected_returned_context_from_state_machine->GetTaskBuilder().BuildTask());
    EXPECT_EQ(expected_next_state, actual_next_state);
}

TEST_F(StatesTests, EditTaskExecuteShouldCreateEditTaskCommand) {
    // Arrange
    std::shared_ptr<StateInterface> expected_state_machine_initial_state = std::make_shared<InputTaskTitleState>(nullptr);
    std::shared_ptr<StateInterface> expected_next_state = std::make_shared<EndState>(nullptr);
    std::shared_ptr<StateContext> expected_returned_context_from_state_machine = GetContextWithFilledTask();
    StateContext edit_task_context;
    EditTaskState edit_task_state(states_factory_);

    // Assert
    ExpectGetUserInput("Task ID", "5");

    EXPECT_CALL(*states_factory_, GetNextState(testing::An<const EditTaskState&>(), StatesFactory::MoveType::NEXT))
            .WillOnce(Return(expected_state_machine_initial_state));
    EXPECT_CALL(*states_factory_, GetNextState(testing::An<const EditTaskState&>(), StatesFactory::MoveType::PREVIOUS))
            .WillOnce(Return(expected_next_state));

    std::unique_ptr<MockStateMachine> state_machine = std::make_unique<MockStateMachine>();
    EXPECT_CALL(*state_machine, Run(testing::_, expected_state_machine_initial_state))
            .WillOnce(Return(expected_returned_context_from_state_machine));
    EXPECT_CALL(*states_factory_, CreateStateMachine())
            .WillOnce(Return(testing::ByMove(std::move(state_machine))));

    EXPECT_CALL(*command_factory_, CreateEditCommand(testing::Ref(edit_task_context))).Times(1);
    // Act
    std::shared_ptr<StateInterface> actual_next_state = edit_task_state.Execute(edit_task_context);
    // Assert
    EXPECT_EQ(edit_task_context.GetTaskBuilder().BuildTask(), expected_returned_context_from_state_machine->GetTaskBuilder().BuildTask());
    EXPECT_EQ(expected_next_state, actual_next_state);
}

TEST_F(StatesTests, EditTaskStateExecuteGivenWrongTaskId_ShouldReturnErrorNextState) {
    // Arrange
    std::shared_ptr<StateInterface> expected_next_state = std::shared_ptr<RootState>(nullptr);
    StateContext edit_task_context;
    EditTaskState edit_task_state(states_factory_);
    // Assert
    ExpectGetUserInput("Task ID", "qwe");

    EXPECT_CALL(*states_factory_, GetNextState(testing::An<const EditTaskState&>(), StatesFactory::MoveType::ERROR))
            .WillOnce(Return(expected_next_state));

    EXPECT_CALL(*console_printer_, WriteError("Incorrect task id was given, try again!")).Times(1);
    // Act
    std::shared_ptr<StateInterface> actual_next_state = edit_task_state.Execute(edit_task_context);
    // Assert
    EXPECT_EQ(expected_next_state, actual_next_state);
}

// Inputting due date with time
TEST_F(StatesTests, InputTaskDueDateStateExecute_ShouldAddTimeToContext) {
    // Arrange
    std::shared_ptr<StateInterface> expected_next_state = std::shared_ptr<EndState>(nullptr);
    StateContext input_due_date_context;
    InputTaskDueDateState input_due_date_state(states_factory_);

    const std::string expected_input_due_date = "16:30 01.01.2030";
    const google::protobuf::Timestamp expected_timestamp = StringToTime(expected_input_due_date).value();
    // Assert
    ExpectGetUserInput("Due Date, format: 12:00 01.01.2000", expected_input_due_date);
    EXPECT_CALL(*states_factory_, GetNextState(testing::An<const InputTaskDueDateState&>(), StatesFactory::MoveType::NEXT))
            .WillOnce(Return(expected_next_state));
    // Act
    std::shared_ptr<StateInterface> actual_next_state = input_due_date_state.Execute(input_due_date_context);
    // Assert
    EXPECT_EQ(expected_next_state, actual_next_state);
    EXPECT_EQ(expected_timestamp, input_due_date_context.GetTaskBuilder().BuildTask().due_date());
}

// Inputting due date without time
TEST_F(StatesTests, InputTaskDueDateStateExecuteGivingDueDateWithoutTime_ShouldPrintError) {
    // Arrange
    std::shared_ptr<StateInterface> expected_next_state = std::shared_ptr<EndState>(nullptr);
    StateContext input_due_date_context;
    InputTaskDueDateState input_due_date_state(states_factory_);

    const std::string expected_input_due_date = "01.01.2030";
    const google::protobuf::Timestamp expected_timestamp = StringToTime(expected_input_due_date, "%d.%m.%Y").value();
    // Assert
    ExpectGetUserInput("Due Date, format: 12:00 01.01.2000", expected_input_due_date);
    EXPECT_CALL(*states_factory_, GetNextState(testing::An<const InputTaskDueDateState&>(), StatesFactory::MoveType::NEXT))
            .WillOnce(Return(expected_next_state));
    // Act
    std::shared_ptr<StateInterface> actual_next_state = input_due_date_state.Execute(input_due_date_context);
    // Assert
    EXPECT_EQ(expected_next_state, actual_next_state);
    EXPECT_EQ(expected_timestamp, input_due_date_context.GetTaskBuilder().BuildTask().due_date());
}

// Inputting incorrect due date
TEST_F(StatesTests, InputTaskDueDateStateExecuteGivingIncorrectDueDate_ShouldPrintError) {
    // Arrange
    std::shared_ptr<StateInterface> expected_next_state = std::shared_ptr<InputTaskDueDateState>(nullptr);
    StateContext input_due_date_context;
    InputTaskDueDateState input_due_date_state(states_factory_);

    const std::string expected_input_due_date = "some text, not due date";
    // Assert
    ExpectGetUserInput("Due Date, format: 12:00 01.01.2000", expected_input_due_date);
    EXPECT_CALL(*states_factory_, GetNextState(testing::An<const InputTaskDueDateState&>(), StatesFactory::MoveType::ERROR))
            .WillOnce(Return(expected_next_state));
    EXPECT_CALL(*console_printer_, WriteError("Wrong due date was given, try again!")).Times(1);
    // Act
    std::shared_ptr<StateInterface> actual_next_state = input_due_date_state.Execute(input_due_date_context);
    // Assert
    EXPECT_EQ(expected_next_state, actual_next_state);
}

// Inputting due date from past
TEST_F(StatesTests, InputTaskDueDateStateExecuteGivingDueDateFromPast_ShouldPrintError) {
    // Arrange
    std::shared_ptr<StateInterface> expected_next_state = std::shared_ptr<InputTaskDueDateState>(nullptr);
    StateContext input_due_date_context;
    InputTaskDueDateState input_due_date_state(states_factory_);

    const std::string expected_input_due_date = "01.01.2011";
    // Assert
    ExpectGetUserInput("Due Date, format: 12:00 01.01.2000", expected_input_due_date);
    EXPECT_CALL(*states_factory_, GetNextState(testing::An<const InputTaskDueDateState&>(), StatesFactory::MoveType::ERROR))
            .WillOnce(Return(expected_next_state));
    EXPECT_CALL(*console_printer_, WriteError("Due time should be in future, try again!")).Times(1);
    // Act
    std::shared_ptr<StateInterface> actual_next_state = input_due_date_state.Execute(input_due_date_context);
    // Assert
    EXPECT_EQ(expected_next_state, actual_next_state);
}

TEST_F(StatesTests, InputTaskPriorityStateExecute_ShouldPutPriorityInContext) {
    // Arrange
    std::shared_ptr<StateInterface> expected_next_state = std::shared_ptr<InputTaskDueDateState>(nullptr);
    StateContext input_priority_context;
    InputTaskPriorityState input_priority_state(states_factory_);

    const std::string expected_input_priority = "Low";
    const Task::Priority expected_priority = StringToTaskPriority(expected_input_priority).value();
    // Assert
    ExpectGetUserInput("Priority (High, Medium, Low, None)", expected_input_priority);
    EXPECT_CALL(*states_factory_, GetNextState(testing::An<const InputTaskPriorityState&>(), StatesFactory::MoveType::NEXT))
            .WillOnce(Return(expected_next_state));
    // Act
    std::shared_ptr<StateInterface> actual_next_state = input_priority_state.Execute(input_priority_context);
    // Assert
    EXPECT_EQ(expected_next_state, actual_next_state);
    EXPECT_EQ(expected_priority, input_priority_context.GetTaskBuilder().BuildTask().priority());
}

TEST_F(StatesTests, InputTaskPriorityStateExecuteGivingIncorrectPriority_ShouldPrintError) {
    // Arrange
    std::shared_ptr<StateInterface> expected_next_state = std::shared_ptr<InputTaskPriorityState>(nullptr);
    StateContext input_priority_context;
    InputTaskPriorityState input_priority_state(states_factory_);

    const std::string expected_input_priority = "some text, not priority";
    // Assert
    ExpectGetUserInput("Priority (High, Medium, Low, None)", expected_input_priority);
    EXPECT_CALL(*states_factory_, GetNextState(testing::An<const InputTaskPriorityState&>(), StatesFactory::MoveType::ERROR))
            .WillOnce(Return(expected_next_state));
    EXPECT_CALL(*console_printer_, WriteError("Wrong task priority was given, try [High, Medium, Low, None]!")).Times(1);
    // Act
    std::shared_ptr<StateInterface> actual_next_state = input_priority_state.Execute(input_priority_context);
    // Assert
    EXPECT_EQ(expected_next_state, actual_next_state);
}

TEST_F(StatesTests, InputTaskTitleStateExecute_ShouldPutTitleInContext) {
    // Arrange
    std::shared_ptr<StateInterface> expected_next_state = std::shared_ptr<InputTaskPriorityState>(nullptr);
    StateContext input_title_context;
    InputTaskTitleState input_title_state(states_factory_);

    const std::string expected_input_title = "Some Task Title";
    // Assert
    ExpectGetUserInput("Title", expected_input_title);
    EXPECT_CALL(*states_factory_, GetNextState(testing::An<const InputTaskTitleState&>(), StatesFactory::MoveType::NEXT))
            .WillOnce(Return(expected_next_state));
    // Act
    std::shared_ptr<StateInterface> actual_next_state = input_title_state.Execute(input_title_context);
    // Assert
    EXPECT_EQ(expected_next_state, actual_next_state);
    EXPECT_EQ(expected_input_title, input_title_context.GetTaskBuilder().BuildTask().title());
}

TEST_F(StatesTests, InputTaskPriorityStateExecuteGivingEmptyTitle_ShouldPrintError) {
    // Arrange
    std::shared_ptr<StateInterface> expected_next_state = std::shared_ptr<InputTaskTitleState>(nullptr);
    StateContext input_title_context;
    InputTaskTitleState input_title_state(states_factory_);

    const std::string expected_input_title = "";
    // Assert
    ExpectGetUserInput("Title", expected_input_title);
    EXPECT_CALL(*states_factory_, GetNextState(testing::An<const InputTaskTitleState&>(), StatesFactory::MoveType::ERROR))
            .WillOnce(Return(expected_next_state));
    EXPECT_CALL(*console_printer_, WriteError("Task title was wrong, please, try again!")).Times(1);
    // Act
    std::shared_ptr<StateInterface> actual_next_state = input_title_state.Execute(input_title_context);
    // Assert
    EXPECT_EQ(expected_next_state, actual_next_state);
}