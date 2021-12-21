//
// Created by Maksym Kharchenko on 03.12.2021.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../mocks/MockWizardStatesFactory.h"
#include "../mocks/MockController.h"
#include "../mocks/MockConsolePrinter.h"
#include "../mocks/MockConsoleReader.h"
#include "../mocks/MockTaskValidator.h"
#include "../mocks/MockModel.h"
#include "../mocks/MockWizardContext.h"
#include "../mocks/MockConsoleStateMachine.h"

#include "Task.pb.h"
#include "utilities/TaskUtilities.h"

#include <google/protobuf/util/time_util.h>

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

    std::shared_ptr<StateContext> context_with_task_;

    TaskId returned_task_id;
    Task returned_task;

    void SetUp() override {
        printer_ = std::make_shared<MockConsolePrinter>();
        reader_ = std::make_shared<MockConsoleReader>();
        task_validator_ = std::make_unique<MockTaskValidator>();
        model_ = std::make_unique<MockModel>();
        controller_ = std::make_shared<MockController>();
        factory_ = std::make_shared<MockWizardStatesFactory>();
        context_ = std::make_shared<MockWizardContext>();

        context_with_task_ = std::make_shared<StateContext>();
        context_with_task_->AddTaskTitle("title");
        context_with_task_->AddTaskPriority(Task::Priority::Task_Priority_NONE);
        context_with_task_->AddTaskDueTime(StringToTime("15:00 01.01.2030").value());

        returned_task_id.set_id(5);

        returned_task.set_title("task!!!!!");
        returned_task.set_priority(Task::Priority::Task_Priority_LOW);
        returned_task.set_allocated_due_date(new google::protobuf::Timestamp(google::protobuf::util::TimeUtil::TimeTToTimestamp(time(0))));
    };

};

// RootState receives nullopt from factory
// Should call GetNextState with MoveType::ERROR
TEST_F(StatesTests, ExecuteRootStateReceivesNulloptFromFactory_ShouldChangeStateToRoot) {
    // Arrange
    RootState root_state{std::make_unique<StateDependencies>(std::make_unique<MockConsoleStateMachine>(),
                                                             factory_,
                                                             controller_,
                                                             printer_,
                                                             reader_)};
    std::shared_ptr<StateInterface> expected_return = std::make_shared<RootState>(nullptr);
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
        .WillOnce(Return(nullptr));
    // Writes error message and call next state with MoveType::ERROR
    EXPECT_CALL(*printer_, WriteError("Unknown command! Use help.")).Times(1);
    EXPECT_CALL(*factory_, GetNextState(testing::An<const RootState&>(), StatesFactory::MoveType::ERROR))
        .Times(1)
        .WillOnce(Return(expected_return));
    // Act
    std::shared_ptr<StateInterface> actual_return = root_state.Execute(context_);
    // Assert
    EXPECT_EQ(expected_return, actual_return);
}

TEST_F(StatesTests, ExecuteRootStateReceivesNotNullFromFactory_ShouldReturnNextState) {
    // Arrange
    RootState root_state{std::make_unique<StateDependencies>(std::make_unique<MockConsoleStateMachine>(),
                                                             factory_,
                                                             controller_,
                                                             printer_,
                                                             reader_)};
    std::shared_ptr<StateInterface> expected_return = std::make_shared<AddTaskState>(nullptr);
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
    std::shared_ptr<StateInterface> actual_return = root_state.Execute(context_);
    // Assert, should return same as factory returned to it
    EXPECT_EQ(expected_return, actual_return);
}

TEST_F(StatesTests, ExecuteQuitStateWithPositiveInput_ShouldCallNextStateNext) {
    // Arrange
    QuitState quit_state{std::make_unique<StateDependencies>(std::make_unique<MockConsoleStateMachine>(),
                                                             factory_,
                                                             controller_,
                                                             printer_,
                                                             reader_)};
    std::shared_ptr<StateInterface> expected_return = std::make_shared<QuitState>(nullptr);
    // Assert
    EXPECT_CALL(*printer_, Write("Are you sure? y/n> ")).Times(1);
    // Receives "y" from user
    EXPECT_CALL(*reader_, ReadLine())
        .Times(1)
        .WillOnce(Return("y"));
    // Calling NextState with MoveState::NEXT, getting expected_return
    EXPECT_CALL(*factory_, GetNextState(testing::An<const QuitState&>(), StatesFactory::MoveType::NEXT))
        .Times(1)
        .WillOnce(Return(expected_return));
    // Act
    std::shared_ptr<StateInterface> actual_return = quit_state.Execute(context_);
    // Assert
    EXPECT_EQ(expected_return, actual_return);
}

TEST_F(StatesTests, ExecuteQuitStateWithNegativeInput_ShouldCallNextStatePrevious) {
    // Arrange
    QuitState quit_state{std::make_unique<StateDependencies>(std::make_unique<MockConsoleStateMachine>(),
                                                             factory_,
                                                             controller_,
                                                             printer_,
                                                             reader_)};
    std::shared_ptr<StateInterface> expected_return = std::make_shared<EndState>(nullptr);
    // Assert
    EXPECT_CALL(*printer_, Write("Are you sure? y/n> ")).Times(1);
    // Receives "y" from user
    EXPECT_CALL(*reader_, ReadLine())
            .Times(1)
            .WillOnce(Return("n"));
    // Calling NextState with MoveState::PREVIOUS, getting expected_return
    EXPECT_CALL(*factory_, GetNextState(testing::An<const QuitState&>(), StatesFactory::MoveType::PREVIOUS))
            .Times(1)
            .WillOnce(Return(expected_return));
    // Act
    std::shared_ptr<StateInterface> actual_return = quit_state.Execute(context_);
    // Assert
    EXPECT_EQ(expected_return, actual_return);
}

TEST_F(StatesTests, ExecuteHelpState_ShouldPrintHelpString) {
    // Arrange
    HelpState help_state {std::make_unique<StateDependencies>(std::make_unique<MockConsoleStateMachine>(),
                                                              factory_,
                                                              controller_,
                                                              printer_,
                                                              reader_)};
    const int expected_strings_printed = 9;
    std::shared_ptr<StateInterface> expected_return = std::make_shared<RootState>(nullptr);
    // Assert
    EXPECT_CALL(*printer_, WriteLine(testing::An<const std::string&>())).Times(11);
    EXPECT_CALL(*factory_, GetNextState(testing::An<const HelpState&>(), StatesFactory::MoveType::NEXT))
        .Times(1)
        .WillOnce(Return(expected_return));
    // Act
    std::shared_ptr<StateInterface> actual_return = help_state.Execute(nullptr);
    // Assert
    EXPECT_EQ(expected_return, actual_return);
}

TEST_F(StatesTests, AddTaskExecute_ShouldRunStateMachineAndGiveTaskToController) {
    // Arrange
    std::unique_ptr<MockConsoleStateMachine> state_machine = std::make_unique<MockConsoleStateMachine>();
    std::shared_ptr<StateInterface> expected_return = std::make_shared<RootState>(nullptr);
    std::shared_ptr<StateInterface> expected_initial_state = std::make_shared<InputTaskTitleState>(nullptr);
    // Assert
    // Expect call factory GetNextState to get initial state for inner state machine
    EXPECT_CALL(*factory_, GetNextState(testing::An<const AddTaskState&>(), StatesFactory::MoveType::NEXT))
        .Times(1)
        .WillOnce(Return(expected_initial_state));
    // Expect running state_machine with initial_state returned by factory
    EXPECT_CALL(*state_machine, Run(testing::_, testing::Eq(expected_initial_state)))
        .Times(1)
        .WillOnce(Return(context_with_task_));
    // Expect giving task from context to controller AddTask method
    EXPECT_CALL(*controller_, AddTask(testing::Eq(context_with_task_->GetTask().value())))
        .Times(1)
        .WillOnce(Return(std::make_pair(TaskActionResult::SUCCESS, returned_task_id)));
    // Expect printing task id
    EXPECT_CALL(*printer_, WriteLine(testing::_)).Times(1);
    // Expect call factory GetNextState with MoveType previous
    EXPECT_CALL(*factory_, GetNextState(testing::An<const AddTaskState&>(), StatesFactory::MoveType::PREVIOUS))
            .Times(1)
            .WillOnce(Return(expected_return));
    // Act
    AddTaskState add_task_state_ {std::make_unique<StateDependencies>(std::move(state_machine),
                                                                      factory_,
                                                                      controller_,
                                                                      printer_,
                                                                      reader_)};
    std::shared_ptr<StateInterface> actual_return = add_task_state_.Execute(nullptr);
    // Expect Execute method return shared_ptr from factory GetNextState method
    EXPECT_EQ(expected_return, actual_return);
}

TEST_F(StatesTests, AddTaskExecute_ShouldRunStateMachineAndPrintError) {
    // Arrange
    std::unique_ptr<MockConsoleStateMachine> state_machine = std::make_unique<MockConsoleStateMachine>();
    std::shared_ptr<StateInterface> expected_return = std::make_shared<RootState>(nullptr);
    std::shared_ptr<StateInterface> expected_initial_state = std::make_shared<InputTaskTitleState>(nullptr);
    // Assert
    // Expect call factory GetNextState to get initial state for inner state machine
    EXPECT_CALL(*factory_, GetNextState(testing::An<const AddTaskState&>(), StatesFactory::MoveType::NEXT))
            .Times(1)
            .WillOnce(Return(expected_initial_state));
    // Expect running state_machine with initial_state returned by factory
    EXPECT_CALL(*state_machine, Run(testing::_, testing::Eq(expected_initial_state)))
            .Times(1)
            .WillOnce(Return(std::make_shared<StateContext>()));
    EXPECT_CALL(*printer_, WriteError("Task wasn't saved.")).Times(1);
    EXPECT_CALL(*factory_, GetNextState(testing::An<const AddTaskState&>(), StatesFactory::MoveType::ERROR))
            .Times(1)
            .WillOnce(Return(expected_return));
    // Act
    AddTaskState add_task_state_ {std::make_unique<StateDependencies>(std::move(state_machine),
                                                                      factory_,
                                                                      controller_,
                                                                      printer_,
                                                                      reader_)};
    std::shared_ptr<StateInterface> actual_return = add_task_state_.Execute(nullptr);
    // Expect Execute method return shared_ptr from factory GetNextState method
    EXPECT_EQ(expected_return, actual_return);
}

TEST_F(StatesTests, AddTaskExecute_ShouldGiveTaskToControllerAndPrintError) {
    // Arrange
    std::unique_ptr<MockConsoleStateMachine> state_machine = std::make_unique<MockConsoleStateMachine>();
    std::shared_ptr<StateInterface> expected_return = std::make_shared<RootState>(nullptr);
    std::shared_ptr<StateInterface> expected_initial_state = std::make_shared<InputTaskTitleState>(nullptr);
    // Assert
    // Expect call factory GetNextState to get initial state for inner state machine
    EXPECT_CALL(*factory_, GetNextState(testing::An<const AddTaskState&>(), StatesFactory::MoveType::NEXT))
            .Times(1)
            .WillOnce(Return(expected_initial_state));
    // Expect running state_machine with initial_state returned by factory
    EXPECT_CALL(*state_machine, Run(testing::_, testing::Eq(expected_initial_state)))
            .Times(1)
            .WillOnce(Return(context_with_task_));
    EXPECT_CALL(*controller_, AddTask(testing::Eq(context_with_task_->GetTask().value())))
            .Times(1)
            .WillOnce(Return(std::make_pair(TaskActionResult::FAIL_INVALID_TASK, returned_task_id)));
    EXPECT_CALL(*printer_, WriteError("Invalid task was given, try again.")).Times(1);
            EXPECT_CALL(*factory_, GetNextState(testing::An<const AddTaskState&>(), StatesFactory::MoveType::ERROR))
                    .Times(1)
                    .WillOnce(Return(expected_return));
    // Act
    AddTaskState add_task_state_ {std::make_unique<StateDependencies>(std::move(state_machine),
                                                                      factory_,
                                                                      controller_,
                                                                      printer_,
                                                                      reader_)};
    std::shared_ptr<StateInterface> actual_return = add_task_state_.Execute(nullptr);
    // Expect Execute method return shared_ptr from factory GetNextState method
    EXPECT_EQ(expected_return, actual_return);
}

TEST_F(StatesTests, AddSubTaskExecute_ShouldRunStateMachineAndGiveTaskToController) {
    // Arrange
    std::unique_ptr<MockConsoleStateMachine> state_machine = std::make_unique<MockConsoleStateMachine>();
    std::shared_ptr<StateInterface> expected_return = std::make_shared<RootState>(nullptr);
    std::shared_ptr<StateInterface> expected_initial_state = std::make_shared<InputTaskTitleState>(nullptr);
    const std::string expected_user_input = "50";
    // Assert
    EXPECT_CALL(*printer_, Write("Parent Task ID> ")).Times(1);
    EXPECT_CALL(*reader_, ReadLine()).Times(1).WillOnce(Return(expected_user_input));
    EXPECT_CALL(*factory_, GetNextState(testing::An<const AddSubTaskState&>(), StatesFactory::MoveType::NEXT))
            .Times(1)
            .WillOnce(Return(expected_initial_state));
    EXPECT_CALL(*state_machine, Run(testing::_, testing::Eq(expected_initial_state)))
        .Times(1)
        .WillOnce(Return(context_with_task_));
    EXPECT_CALL(*controller_, AddSubTask(context_with_task_->GetTask().value(), StringToTaskId(expected_user_input).value()))
        .Times(1)
        .WillOnce(Return(std::make_pair(TaskActionResult::SUCCESS, returned_task_id)));
    EXPECT_CALL(*printer_, WriteLine("Subtask was successfully added. Task id: " + std::to_string(returned_task_id.id())))
        .Times(1);
    EXPECT_CALL(*factory_, GetNextState(testing::An<const AddSubTaskState&>(), StatesFactory::MoveType::PREVIOUS))
            .Times(1)
            .WillOnce(Return(expected_return));
    // Act
    AddSubTaskState add_subtask_state {std::make_unique<StateDependencies>(std::move(state_machine),
                                                                           factory_,
                                                                           controller_,
                                                                           printer_,
                                                                           reader_)};
    std::shared_ptr<StateInterface> actual_return = add_subtask_state.Execute(nullptr);
    // Expect Execute method return shared_ptr from factory GetNextState method
    EXPECT_EQ(expected_return, actual_return);
}

TEST_F(StatesTests, AddSubTaskExecute_ShouldWriteErrorOnNoTaskGivenFromStateMachine) {
    // Arrange
    std::unique_ptr<MockConsoleStateMachine> state_machine = std::make_unique<MockConsoleStateMachine>();
    std::shared_ptr<StateInterface> expected_return = std::make_shared<RootState>(nullptr);
    std::shared_ptr<StateInterface> expected_initial_state = std::make_shared<InputTaskTitleState>(nullptr);
    const std::string expected_user_input = "50";
    // Assert
    EXPECT_CALL(*printer_, Write("Parent Task ID> ")).Times(1);
    EXPECT_CALL(*reader_, ReadLine()).Times(1).WillOnce(Return(expected_user_input));
    EXPECT_CALL(*factory_, GetNextState(testing::An<const AddSubTaskState&>(), StatesFactory::MoveType::NEXT))
            .Times(1)
            .WillOnce(Return(expected_initial_state));
    EXPECT_CALL(*state_machine, Run(testing::_, testing::Eq(expected_initial_state)))
            .Times(1)
            .WillOnce(Return(std::make_shared<StateContext>()));
    EXPECT_CALL(*printer_, WriteError("Invalid task was given, try again.")).Times(1);
    EXPECT_CALL(*factory_, GetNextState(testing::An<const AddSubTaskState&>(), StatesFactory::MoveType::ERROR))
            .Times(1)
            .WillOnce(Return(expected_return));
    // Act
    AddSubTaskState add_subtask_state {std::make_unique<StateDependencies>(std::move(state_machine),
                                                                           factory_,
                                                                           controller_,
                                                                           printer_,
                                                                           reader_)};
    std::shared_ptr<StateInterface> actual_return = add_subtask_state.Execute(nullptr);
    // Expect Execute method return shared_ptr from factory GetNextState method
    EXPECT_EQ(expected_return, actual_return);
}

TEST_F(StatesTests, AddSubTaskExecute_ShouldWriteErrorOnNoSuchTask) {
    // Arrange
    std::unique_ptr<MockConsoleStateMachine> state_machine = std::make_unique<MockConsoleStateMachine>();
    std::shared_ptr<StateInterface> expected_return = std::make_shared<InputTaskDueDateState>(nullptr);
    std::shared_ptr<StateInterface> expected_initial_state = std::make_shared<InputTaskTitleState>(nullptr);
    const std::string expected_user_input = "50";
    // Assert
    EXPECT_CALL(*printer_, Write("Parent Task ID> ")).Times(1);
    EXPECT_CALL(*reader_, ReadLine()).Times(1).WillOnce(Return(expected_user_input));
    EXPECT_CALL(*factory_, GetNextState(testing::An<const AddSubTaskState&>(), StatesFactory::MoveType::NEXT))
            .Times(1)
            .WillOnce(Return(expected_initial_state));
    EXPECT_CALL(*state_machine, Run(testing::_, testing::Eq(expected_initial_state)))
            .Times(1)
            .WillOnce(Return(context_with_task_));
    EXPECT_CALL(*controller_, AddSubTask(context_with_task_->GetTask().value(), StringToTaskId(expected_user_input).value()))
            .Times(1)
            .WillOnce(Return(std::make_pair(TaskActionResult::FAIL_NO_SUCH_TASK, std::nullopt)));
    EXPECT_CALL(*printer_, WriteError("No parent task with this id was found."))
            .Times(1);
    EXPECT_CALL(*factory_, GetNextState(testing::An<const AddSubTaskState&>(), StatesFactory::MoveType::ERROR))
            .Times(1)
            .WillOnce(Return(expected_return));
    // Act
    AddSubTaskState add_subtask_state {std::make_unique<StateDependencies>(std::move(state_machine),
                                                                           factory_,
                                                                           controller_,
                                                                           printer_,
                                                                           reader_)};
    std::shared_ptr<StateInterface> actual_return = add_subtask_state.Execute(nullptr);
    // Expect Execute method return shared_ptr from factory GetNextState method
    EXPECT_EQ(expected_return, actual_return);
}

TEST_F(StatesTests, AddSubTaskExecuteWrongTaskIdInput_ShouldReturnOnPreviousState) {
    // Arrange
    AddSubTaskState add_subtask_state {std::make_unique<StateDependencies>(std::make_unique<MockConsoleStateMachine>(),
                                                                           factory_,
                                                                           controller_,
                                                                           printer_,
                                                                           reader_)};
    std::shared_ptr<StateInterface> expected_return = std::make_shared<RootState>(nullptr);
    // Assert
    EXPECT_CALL(*reader_, ReadLine()).Times(1).WillOnce(Return("asfasfasf"));
    EXPECT_CALL(*factory_, GetNextState(testing::An<const AddSubTaskState&>(), StatesFactory::MoveType::PREVIOUS))
            .Times(1)
            .WillOnce(Return(expected_return));
    // Act
    std::shared_ptr<StateInterface> actual_return = add_subtask_state.Execute(nullptr);
    // Assert
    EXPECT_EQ(expected_return, actual_return);
}

TEST_F(StatesTests, InputTaskTitleExecute_ShouldAskUserForTitleAndWriteItToContext) {
    // Arrange
    InputTaskTitleState input_title_state {std::make_unique<StateDependencies>(std::make_unique<MockConsoleStateMachine>(),
                                                                               factory_,
                                                                               controller_,
                                                                               printer_,
                                                                               reader_)};
    const std::string expected_input_title = "task title";
    std::shared_ptr<StateInterface> expected_return = std::make_shared<InputTaskPriorityState>(nullptr);
    // Assert
    EXPECT_CALL(*context_, GetTaskId()).Times(1).WillOnce(Return(std::nullopt));
    EXPECT_CALL(*printer_, Write("Title> ")).Times(1);
    EXPECT_CALL(*reader_, ReadLine()).Times(1).WillOnce(Return(expected_input_title));
    EXPECT_CALL(*context_, AddTaskTitle(expected_input_title)).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*factory_, GetNextState(testing::An<const InputTaskTitleState&>(), StatesFactory::MoveType::NEXT))
            .Times(1)
            .WillOnce(Return(expected_return));
    // Act
    std::shared_ptr<StateInterface> actual_return = input_title_state.Execute(context_);
    // Assert
    EXPECT_EQ(expected_return, actual_return);
}

TEST_F(StatesTests, InputTaskTitleExecute_ShouldAskUserToEditTitle) {
    // Arrange
    InputTaskTitleState input_title_state {std::make_unique<StateDependencies>(std::make_unique<MockConsoleStateMachine>(),
                                                                               factory_,
                                                                               controller_,
                                                                               printer_,
                                                                               reader_)};
    const std::string expected_old_title = "old title";
    returned_task.set_title(expected_old_title);
    const std::string expected_input_title = "task title";
    std::shared_ptr<StateInterface> expected_return = std::make_shared<InputTaskTitleState>(nullptr);
    // Assert
    EXPECT_CALL(*context_, GetTaskId()).Times(1).WillOnce(Return(returned_task_id));
    EXPECT_CALL(*context_, GetTask())
        .Times(1)
        .WillOnce(Return(returned_task));
    EXPECT_CALL(*printer_, WriteLine("Leave empty for default value.")).Times(1);
    EXPECT_CALL(*printer_, Write("Title, default: " + expected_old_title + "> ")).Times(1);
    EXPECT_CALL(*reader_, ReadLine()).Times(1).WillOnce(Return(expected_input_title));
    EXPECT_CALL(*context_, AddTaskTitle(expected_input_title)).Times(1).WillOnce(Return(false));
    EXPECT_CALL(*printer_, WriteError("Task title was wrong, please, try again!")).Times(1);
    EXPECT_CALL(*factory_, GetNextState(testing::An<const InputTaskTitleState&>(), StatesFactory::MoveType::ERROR))
            .Times(1)
            .WillOnce(Return(expected_return));
    // Act
    std::shared_ptr<StateInterface> actual_return = input_title_state.Execute(context_);
    // Assert
    EXPECT_EQ(expected_return, actual_return);
}

TEST_F(StatesTests, InputTaskTitleExecute_ShouldAskUserToEditTitleSetDefaultValue) {
    // Arrange
    InputTaskTitleState input_title_state {std::make_unique<StateDependencies>(std::make_unique<MockConsoleStateMachine>(),
                                                                               factory_,
                                                                               controller_,
                                                                               printer_,
                                                                               reader_)};
    const std::string expected_old_title = "old title";
    returned_task.set_title(expected_old_title);
    // Assert
    EXPECT_CALL(*context_, GetTaskId()).Times(1).WillOnce(Return(returned_task_id));
    EXPECT_CALL(*context_, GetTask())
            .Times(1)
            .WillOnce(Return(returned_task));
    EXPECT_CALL(*printer_, WriteLine("Leave empty for default value.")).Times(1);
    EXPECT_CALL(*printer_, Write("Title, default: " + expected_old_title + "> ")).Times(1);
    EXPECT_CALL(*reader_, ReadLine()).Times(1).WillOnce(Return(""));
    EXPECT_CALL(*context_, AddTaskTitle(expected_old_title)).Times(1).WillOnce(Return(true));
    // Act
    input_title_state.Execute(context_);
}

TEST_F(StatesTests, InputTaskDueDateExecute_ShouldAskUserForDueDateAndWriteToContext) {
    // Arrange
    InputTaskDueDateState input_due_date_state {std::make_unique<StateDependencies>(std::make_unique<MockConsoleStateMachine>(),
                                                                                    factory_,
                                                                                    controller_,
                                                                                    printer_,
                                                                                    reader_)};
    const std::string expected_input_due_date = "15:00 01.01.2025";
    google::protobuf::Timestamp expected_due_time = StringToTime(expected_input_due_date).value();
    std::shared_ptr<StateInterface> expected_return = nullptr;
    // Assert
    EXPECT_CALL(*context_, GetTaskId()).Times(1).WillOnce(Return(std::nullopt));
    EXPECT_CALL(*printer_, Write("Due Date, format: 12:00 01.01.2000> ")).Times(1);
    EXPECT_CALL(*reader_, ReadLine()).Times(1).WillOnce(Return(expected_input_due_date));
    EXPECT_CALL(*context_, AddTaskDueTime(expected_due_time)).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*factory_, GetNextState(testing::An<const InputTaskDueDateState&>(), StatesFactory::MoveType::NEXT))
        .Times(1)
        .WillOnce(Return(nullptr));
    // Act
    std::shared_ptr<StateInterface> actual_return = input_due_date_state.Execute(context_);
    // Assert
    EXPECT_EQ(expected_return, actual_return);
}

TEST_F(StatesTests, InputTaskDueDateExecute_ShouldAskUserToEdit) {
    // Arrange
    std::shared_ptr<StateInterface> expected_return = std::make_shared<InputTaskDueDateState>(nullptr);
    InputTaskDueDateState input_due_date_state {std::make_unique<StateDependencies>(std::make_unique<MockConsoleStateMachine>(),
                                                                                    factory_,
                                                                                    controller_,
                                                                                    printer_,
                                                                                    reader_)};
    google::protobuf::Timestamp old_due_date = StringToTime("15:00 01.01.2025").value();
    returned_task.set_allocated_due_date(new google::protobuf::Timestamp(old_due_date));
    std::string new_input = "guuuuuuuu";
    // Assert
    EXPECT_CALL(*context_, GetTaskId()).Times(1).WillOnce(Return(returned_task_id));
    EXPECT_CALL(*context_, GetTask())
        .Times(1)
        .WillOnce(Return(returned_task));
    EXPECT_CALL(*printer_, Write("Due Date, default: " + TimeToString(old_due_date) + "> ")).Times(1);
    EXPECT_CALL(*reader_, ReadLine()).Times(1).WillOnce(Return(new_input));
    EXPECT_CALL(*printer_, WriteError("Wrong due date was given, try again!"));
    EXPECT_CALL(*factory_, GetNextState(testing::An<const InputTaskDueDateState&>(), StatesFactory::MoveType::ERROR))
        .Times(1)
        .WillOnce(Return(expected_return));
    // Act
    std::shared_ptr<StateInterface> actual_return = input_due_date_state.Execute(context_);
    // Assert
    EXPECT_EQ(expected_return, actual_return);
}

TEST_F(StatesTests, InputTaskDueDateExecute_ShouldSetPreviousValueOnEmptyUserInput) {
    // Arrange
    InputTaskDueDateState input_due_date_state {std::make_unique<StateDependencies>(std::make_unique<MockConsoleStateMachine>(),
                                                                                    factory_,
                                                                                    controller_,
                                                                                    printer_,
                                                                                    reader_)};
    google::protobuf::Timestamp expected_due_time = StringToTime("15:00 01.01.2025").value();
    std::shared_ptr<StateInterface> expected_return = nullptr;
    // Assert
    EXPECT_CALL(*context_, GetTaskId()).Times(1).WillOnce(Return(returned_task_id));
    returned_task.set_allocated_due_date(new google::protobuf::Timestamp(expected_due_time));
    EXPECT_CALL(*context_, GetTask())
        .Times(1)
        .WillOnce(Return(returned_task));
    EXPECT_CALL(*reader_, ReadLine()).Times(1).WillOnce(Return(""));
    EXPECT_CALL(*context_, AddTaskDueTime(expected_due_time)).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*factory_, GetNextState(testing::An<const InputTaskDueDateState&>(), StatesFactory::MoveType::NEXT))
        .Times(1)
        .WillOnce(Return(nullptr));
    // Act
    std::shared_ptr<StateInterface> actual_return = input_due_date_state.Execute(context_);
    // Assert
    EXPECT_EQ(expected_return, actual_return);
}

TEST_F(StatesTests, InputDueDateExecuteWithPastDate_ShouldWriteError) {
    // Arrange
    InputTaskDueDateState input_due_date_state {std::make_unique<StateDependencies>(std::make_unique<MockConsoleStateMachine>(),
                                                                                    factory_,
                                                                                    controller_,
                                                                                    printer_,
                                                                                    reader_)};
    const std::string expected_input_due_date = "15:00 01.01.2025";
    google::protobuf::Timestamp expected_due_time = StringToTime(expected_input_due_date).value();
    std::shared_ptr<StateInterface> expected_return = std::make_shared<InputTaskDueDateState>(nullptr);
    // Assert
    EXPECT_CALL(*context_, GetTaskId()).Times(1).WillOnce(Return(std::nullopt));
    EXPECT_CALL(*printer_, Write("Due Date, format: 12:00 01.01.2000> ")).Times(1);
    EXPECT_CALL(*reader_, ReadLine()).Times(1).WillOnce(Return(expected_input_due_date));
    EXPECT_CALL(*context_, AddTaskDueTime(expected_due_time)).Times(1).WillOnce(Return(false));
    EXPECT_CALL(*printer_, WriteError("Due time should be in future, try again!")).Times(1);
    EXPECT_CALL(*factory_, GetNextState(testing::An<const InputTaskDueDateState&>(), StatesFactory::MoveType::ERROR))
            .Times(1)
            .WillOnce(Return(expected_return));
    // Act
    std::shared_ptr<StateInterface> actual_return = input_due_date_state.Execute(context_);
    // Assert
    EXPECT_EQ(expected_return, actual_return);
}
