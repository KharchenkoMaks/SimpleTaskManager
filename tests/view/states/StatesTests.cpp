//
// Created by Maksym Kharchenko on 03.12.2021.
//

#include "gtest/gtest.h"

#include "../mocks/MockWizardStatesFactory.h"
#include "../mocks/MockController.h"
#include "../mocks/MockConsolePrinter.h"
#include "../mocks/MockConsoleReader.h"
#include "../mocks/MockTaskValidator.h"
#include "../mocks/MockModel.h"
#include "../mocks/MockWizardContext.h"
#include "../mocks/MockConsoleStateMachine.h"

#include "DueTime.h"

using ::testing::Return;

class StatesTests : public ::testing::Test {
public:
    std::shared_ptr<MockConsolePrinter> printer_;
    std::shared_ptr<MockConsoleReader> reader_;
    std::shared_ptr<MockTaskValidator> task_validator_;
    std::shared_ptr<MockModel> model_;
    std::shared_ptr<MockController> controller_;
    std::shared_ptr<MockWizardStatesFactory> factory_;
    std::shared_ptr<MockWizardContext> context_;
    std::shared_ptr<MockConsoleStateMachine> state_machine_;

    std::shared_ptr<WizardContext> context_with_task;

    void SetUp() override {
        printer_ = std::make_shared<MockConsolePrinter>();
        reader_ = std::make_shared<MockConsoleReader>();
        task_validator_ = std::make_unique<MockTaskValidator>();
        model_ = std::make_unique<MockModel>();
        controller_ = std::make_shared<MockController>(std::make_unique<MockModel>(), std::make_unique<MockTaskValidator>());
        factory_ = std::make_shared<MockWizardStatesFactory>(controller_, printer_, reader_);
        context_ = std::make_shared<MockWizardContext>();
        state_machine_ = std::make_shared<MockConsoleStateMachine>();

        context_with_task = std::make_shared<WizardContext>();
        context_with_task->AddTaskTitle("title");
        context_with_task->AddTaskPriority(Task::Priority::NONE);
        context_with_task->AddTaskDueTime(DueTime::Create("15:00 01.01.2030").value());
    };

};

// RootState receives nullopt from factory
// Should call GetNextState with MoveType::ERROR
TEST_F(StatesTests, ExecuteRootStateReceivesNulloptFromFactory_ShouldChangeStateToRoot) {
    // Arrange
    this->SetUp();
    RootState root_state{factory_, printer_, reader_ };
    std::optional<std::shared_ptr<WizardStateConsole>> expected_return =
            std::make_shared<RootState>(nullptr, nullptr, nullptr);
    // Assert
    // Invites user to input command
    EXPECT_CALL(*printer_, Write("> ")).Times(1);
    // Receives cmd
    EXPECT_CALL(*reader_, ReadLine())
            .Times(1)
            .WillOnce(Return("cmd"));
    // Gives received command to factory and receives nullopt
    EXPECT_CALL(*factory_, GetStateByCommand("cmd"))
        .Times(1)
        .WillOnce(Return(std::nullopt));
    // Writes error message and call next state with MoveType::ERROR
    EXPECT_CALL(*printer_, WriteError("Unknown command! Use help.")).Times(1);
    EXPECT_CALL(*factory_, GetNextState(testing::An<const RootState&>(), WizardStatesFactory::MoveType::ERROR))
        .Times(1)
        .WillOnce(Return(expected_return));
    // Act
    std::optional<std::shared_ptr<WizardStateConsole>> actual_return = root_state.Execute(context_);
    // Assert
    EXPECT_EQ(expected_return, actual_return);
}

TEST_F(StatesTests, ExecuteRootStateReceivesNotNullFromFactory_ShouldReturnNextState) {
    // Arrange
    this->SetUp();
    RootState root_state{factory_, printer_, reader_ };
    std::optional<std::shared_ptr<WizardStateConsole>> expected_return =
            std::make_shared<AddTaskState>(nullptr, nullptr, nullptr, nullptr, nullptr);
    // Assert
    // Invites user to input command
    EXPECT_CALL(*printer_, Write("> ")).Times(1);
    // Receives cmd
    EXPECT_CALL(*reader_, ReadLine())
            .Times(1)
            .WillOnce(Return("add"));
    // Gives received command to factory and receives AddTaskState
    EXPECT_CALL(*factory_, GetStateByCommand("add"))
            .Times(1)
            .WillOnce(Return(expected_return));
    std::optional<std::shared_ptr<WizardStateConsole>> actual_return = root_state.Execute(context_);
    // Assert, should return same as factory returned to it
    EXPECT_EQ(expected_return, actual_return);
}

TEST_F(StatesTests, ExecuteQuitStateWithPositiveInput_ShouldCallNextStateNext) {
    // Arrange
    this->SetUp();
    QuitState quit_state{ factory_, printer_, reader_ };
    std::optional<std::shared_ptr<WizardStateConsole>> expected_return =
            std::make_shared<QuitState>(nullptr, nullptr, nullptr);
    // Assert
    EXPECT_CALL(*printer_, Write("Are you sure? y/n> ")).Times(1);
    // Receives "y" from user
    EXPECT_CALL(*reader_, ReadLine())
        .Times(1)
        .WillOnce(Return("y"));
    // Calling NextState with MoveState::NEXT, getting expected_return
    EXPECT_CALL(*factory_, GetNextState(testing::An<const QuitState&>(), WizardStatesFactory::MoveType::NEXT))
        .Times(1)
        .WillOnce(Return(expected_return));
    // Act
    std::optional<std::shared_ptr<WizardStateConsole>> actual_return = quit_state.Execute(context_);
    // Assert
    EXPECT_EQ(expected_return, actual_return);
}

TEST_F(StatesTests, ExecuteQuitStateWithNegativeInput_ShouldCallNextStatePrevious) {
    // Arrange
    this->SetUp();
    QuitState quit_state{ factory_, printer_, reader_ };
    std::optional<std::shared_ptr<WizardStateConsole>> expected_return = std::nullopt;
    // Assert
    EXPECT_CALL(*printer_, Write("Are you sure? y/n> ")).Times(1);
    // Receives "y" from user
    EXPECT_CALL(*reader_, ReadLine())
            .Times(1)
            .WillOnce(Return("n"));
    // Calling NextState with MoveState::PREVIOUS, getting expected_return
    EXPECT_CALL(*factory_, GetNextState(testing::An<const QuitState&>(), WizardStatesFactory::MoveType::PREVIOUS))
            .Times(1)
            .WillOnce(Return(expected_return));
    // Act
    std::optional<std::shared_ptr<WizardStateConsole>> actual_return = quit_state.Execute(context_);
    // Assert
    EXPECT_EQ(expected_return, actual_return);
}

TEST_F(StatesTests, ExecuteShowState_ShouldPrintStringReceivedFromController) {
    // Arrange
    this->SetUp();
    ShowState show_state{ controller_, factory_, printer_, nullptr };
    std::optional<std::shared_ptr<WizardStateConsole>> expected_return =
            std::make_shared<RootState>(nullptr, nullptr, nullptr);
    const std::string expected_print = "tasks string";
    // Assert
    EXPECT_CALL(*controller_, GetAllTasks())
        .Times(1)
        .WillOnce(Return(expected_print));
    EXPECT_CALL(*printer_, Write(expected_print)).Times(1);
    EXPECT_CALL(*factory_, GetNextState(testing::An<const ShowState&>(), WizardStatesFactory::MoveType::NEXT))
            .Times(1)
            .WillOnce(Return(expected_return));
    // Act
    std::optional<std::shared_ptr<WizardStateConsole>> actual_return = show_state.Execute(context_);
    // Assert
    EXPECT_EQ(expected_return, actual_return);
}

TEST_F(StatesTests, ExecuteShowState_ShouldPrintHelpString) {
    // Arrange
    this->SetUp();
    HelpState help_state {factory_, printer_, nullptr};
    const int expected_strings_printed = 9;
    std::optional<std::shared_ptr<WizardStateConsole>> expected_return =
            std::make_shared<RootState>(nullptr, nullptr, nullptr);
    // Assert
    EXPECT_CALL(*printer_, WriteLine(testing::An<const std::string&>())).Times(9);
    EXPECT_CALL(*factory_, GetNextState(testing::An<const HelpState&>(), WizardStatesFactory::MoveType::NEXT))
        .Times(1)
        .WillOnce(Return(expected_return));
    // Act
    std::optional<std::shared_ptr<WizardStateConsole>> actual_return = help_state.Execute(nullptr);
    // Assert
    EXPECT_EQ(expected_return, actual_return);
}

TEST_F(StatesTests, AddTaskExecute_ShouldRunStateMachineAndGiveTaskToController) {
    // Arrange
    this->SetUp();
    AddTaskState add_task_state_ {state_machine_, controller_, factory_, printer_, nullptr };
    std::optional<std::shared_ptr<WizardStateConsole>> expected_return =
            std::make_shared<RootState>(nullptr, nullptr, nullptr);
    const TaskId returned_task_id = TaskId::Create(5).value();
    std::optional<std::shared_ptr<WizardStateConsole>> expected_initial_state =
            std::make_shared<InputTaskTitleState>(nullptr, nullptr, nullptr);
    // Assert
    // Expect call factory GetNextState to get initial state for inner state machine
    EXPECT_CALL(*factory_, GetNextState(testing::An<const AddTaskState&>(), WizardStatesFactory::MoveType::NEXT))
        .Times(1)
        .WillOnce(Return(expected_initial_state));
    // Expect running state_machine with initial_state returned by factory
    EXPECT_CALL(*state_machine_, Run(testing::_, testing::Eq(expected_initial_state)))
        .Times(1)
        .WillOnce(Return(context_with_task));
    // Expect giving task from context to controller AddTask method
    EXPECT_CALL(*controller_, AddTask(testing::Eq(context_with_task->GetTask().value())))
        .Times(1)
        .WillOnce(Return(returned_task_id));
    // Expect printing task id
    EXPECT_CALL(*printer_, WriteLine(testing::_)).Times(1);
    // Expect call factory GetNextState with MoveType previous
    EXPECT_CALL(*factory_, GetNextState(testing::An<const AddTaskState&>(), WizardStatesFactory::MoveType::PREVIOUS))
            .Times(1)
            .WillOnce(Return(expected_return));
    // Act
    std::optional<std::shared_ptr<WizardStateConsole>> actual_return = add_task_state_.Execute(nullptr);
    // Expect Execute method return shared_ptr from factory GetNextState method
    EXPECT_EQ(expected_return, actual_return);
}

TEST_F(StatesTests, AddTaskExecute_ShouldRunStateMachineAndPrintError) {
    // Arrange
    this->SetUp();
    AddTaskState add_task_state_ {state_machine_, controller_, factory_, printer_, nullptr };
    std::optional<std::shared_ptr<WizardStateConsole>> expected_return =
            std::make_shared<RootState>(nullptr, nullptr, nullptr);
    std::optional<std::shared_ptr<WizardStateConsole>> expected_initial_state =
            std::make_shared<InputTaskTitleState>(nullptr, nullptr, nullptr);
    // Assert
    // Expect call factory GetNextState to get initial state for inner state machine
    EXPECT_CALL(*factory_, GetNextState(testing::An<const AddTaskState&>(), WizardStatesFactory::MoveType::NEXT))
            .Times(1)
            .WillOnce(Return(expected_initial_state));
    // Expect running state_machine with initial_state returned by factory
    EXPECT_CALL(*state_machine_, Run(testing::_, testing::Eq(expected_initial_state)))
            .Times(1)
            .WillOnce(Return(std::make_shared<WizardContext>()));
    EXPECT_CALL(*printer_, WriteError(testing::_)).Times(1);
    EXPECT_CALL(*factory_, GetNextState(testing::An<const AddTaskState&>(), WizardStatesFactory::MoveType::ERROR))
            .Times(1)
            .WillOnce(Return(expected_return));
    // Act
    std::optional<std::shared_ptr<WizardStateConsole>> actual_return = add_task_state_.Execute(nullptr);
    // Expect Execute method return shared_ptr from factory GetNextState method
    EXPECT_EQ(expected_return, actual_return);
}

TEST_F(StatesTests, InputTaskTitleExecute_ShouldAskUserForTitleAndWriteItToContext) {
    // Arrange
    this->SetUp();
    InputTaskTitleState input_title_state {factory_, printer_, reader_};
    const std::string expected_input_title = "task title";
    std::optional<std::shared_ptr<WizardStateConsole>> expected_return =
            std::make_shared<InputTaskPriorityState>(nullptr, nullptr, nullptr);
    // Assert
    EXPECT_CALL(*context_, GetTaskId()).Times(1).WillOnce(Return(std::nullopt));
    EXPECT_CALL(*printer_, Write("Title> ")).Times(1);
    EXPECT_CALL(*reader_, ReadLine()).Times(1).WillOnce(Return(expected_input_title));
    EXPECT_CALL(*context_, AddTaskTitle(expected_input_title)).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*factory_, GetNextState(testing::An<const InputTaskTitleState&>(), WizardStatesFactory::MoveType::NEXT))
            .Times(1)
            .WillOnce(Return(expected_return));
    // Act
    std::optional<std::shared_ptr<WizardStateConsole>> actual_return = input_title_state.Execute(context_);
    // Assert
    EXPECT_EQ(expected_return, actual_return);
}

TEST_F(StatesTests, InputTaskTitleExecute_ShouldAskUserToEditTitle) {
    // Arrange
    this->SetUp();
    InputTaskTitleState input_title_state {factory_, printer_, reader_};
    const std::string expected_old_title = "old title";
    const std::string expected_input_title = "task title";
    std::optional<std::shared_ptr<WizardStateConsole>> expected_return =
            std::make_shared<InputTaskTitleState>(nullptr, nullptr, nullptr);
    // Assert
    EXPECT_CALL(*context_, GetTaskId()).Times(1).WillOnce(Return(TaskId::Create(5).value()));
    EXPECT_CALL(*context_, GetTask())
        .Times(1)
        .WillOnce(Return(Task::Create(expected_old_title, Task::Priority::NONE, DueTime::Create(time(0) + 1000))));
    EXPECT_CALL(*printer_, WriteLine("Leave empty for default value.")).Times(1);
    EXPECT_CALL(*printer_, Write("Title, default: " + expected_old_title + "> ")).Times(1);
    EXPECT_CALL(*reader_, ReadLine()).Times(1).WillOnce(Return(expected_input_title));
    EXPECT_CALL(*context_, AddTaskTitle(expected_input_title)).Times(1).WillOnce(Return(false));
    EXPECT_CALL(*printer_, WriteError("Task title was wrong, please, try again!")).Times(1);
    EXPECT_CALL(*factory_, GetNextState(testing::An<const InputTaskTitleState&>(), WizardStatesFactory::MoveType::ERROR))
            .Times(1)
            .WillOnce(Return(expected_return));
    // Act
    std::optional<std::shared_ptr<WizardStateConsole>> actual_return = input_title_state.Execute(context_);
    // Assert
    EXPECT_EQ(expected_return, actual_return);
}

TEST_F(StatesTests, InputTaskTitleExecute_ShouldAskUserToEditTitleSetDefaultValue) {
    // Arrange
    this->SetUp();
    InputTaskTitleState input_title_state {factory_, printer_, reader_};
    const std::string expected_old_title = "old title";
    // Assert
    EXPECT_CALL(*context_, GetTaskId()).Times(1).WillOnce(Return(TaskId::Create(5).value()));
    EXPECT_CALL(*context_, GetTask())
            .Times(1)
            .WillOnce(Return(Task::Create(expected_old_title, Task::Priority::NONE, DueTime::Create(time(0) + 1000))));
    EXPECT_CALL(*printer_, WriteLine("Leave empty for default value.")).Times(1);
    EXPECT_CALL(*printer_, Write("Title, default: " + expected_old_title + "> ")).Times(1);
    EXPECT_CALL(*reader_, ReadLine()).Times(1).WillOnce(Return(""));
    EXPECT_CALL(*context_, AddTaskTitle(expected_old_title)).Times(1).WillOnce(Return(true));
    // Act
    input_title_state.Execute(context_);
}