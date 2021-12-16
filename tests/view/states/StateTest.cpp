//
// Created by Maksym Kharchenko on 13.12.2021.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "states/ShowState.h"

#include "../mocks/MockStateDependencies.h"
#include "../mocks/MockWizardContext.h"
#include "../mocks/MockConsolePrinter.h"
#include "../mocks/MockConsoleReader.h"
#include "../mocks/MockWizardStatesFactory.h"
#include "../mocks/MockController.h"

#include "utilities/TaskUtilities.h"
#include "Task.pb.h"

#include <vector>
#include <utility>

using ::testing::Return;
using ::testing::An;

class StateTest : public ::testing::Test {
public:
    enum class PrintForm {
        WRITE,
        WRITE_LINE,
        WRITE_ERROR
    };
public:
    std::unique_ptr<MockStateDependencies> dependencies_;
    std::shared_ptr<MockWizardContext> wizard_context_;
    std::shared_ptr<MockConsolePrinter> printer_;
    std::shared_ptr<MockConsoleReader> reader_;
    std::shared_ptr<MockWizardStatesFactory> factory_;
    std::shared_ptr<MockController> controller_;
public:
    void SetUp() override {
        dependencies_ = std::make_unique<MockStateDependencies>();
        wizard_context_ = std::make_shared<MockWizardContext>();
        printer_ = std::make_shared<MockConsolePrinter>();
        reader_ = std::make_shared<MockConsoleReader>();
        factory_ = std::make_shared<MockWizardStatesFactory>();
        controller_ = std::make_shared<MockController>();

        EXPECT_CALL(*dependencies_, GetConsolePrinter())
                .WillRepeatedly(testing::Return(printer_));
        EXPECT_CALL(*dependencies_, GetStatesFactory()).WillRepeatedly(Return(factory_));
        EXPECT_CALL(*dependencies_, GetController()).WillRepeatedly(Return(controller_));
    }
    void ExecuteAndExpectReturn(const std::shared_ptr<WizardStateInterface>& testing_state,
                                const std::shared_ptr<WizardStateInterface>& expected_next_state) {
        // Execute state
        std::shared_ptr<WizardStateInterface> actual_next_state = testing_state->Execute(wizard_context_);
        // Assert
        EXPECT_EQ(expected_next_state, actual_next_state);
    }
    void AddExpectedPrint(PrintForm print_form, const std::string& print_message) {
        switch(print_form) {
            case PrintForm::WRITE: {
                EXPECT_CALL(*printer_, Write(print_message)).Times(1);
                break;
            }
            case PrintForm::WRITE_LINE: {
                EXPECT_CALL(*printer_, WriteLine(print_message)).Times(1);
                break;
            }
            case PrintForm::WRITE_ERROR: {
                EXPECT_CALL(*printer_, WriteError(print_message)).Times(1);
                break;
            }
        }
    }
    void AddExpectedRead(const std::string& invitation_message,
                         const std::string& return_string) {
        EXPECT_CALL(*dependencies_, GetUserInput(invitation_message))
                .Times(1)
                .WillOnce(Return(return_string));
    }
    void AddExpectedReadId(const std::string& invitation_message,
                           const std::optional<TaskId>& return_task_id) {
        EXPECT_CALL(*dependencies_, GetTaskIdFromUser(invitation_message))
                .Times(1)
                .WillOnce(Return(return_task_id));
    }
};

TEST_F(StateTest, ShowStateExecute_ShouldPrintTasksReceivedFromController) {
    // Arrange
    TaskId parent_task_id;
    TaskId task2_id;
    task2_id.set_id(2);
    TaskId task3_id;
    task3_id.set_id(3);
    Task t1;
    t1.set_title("task1");
    t1.set_priority(Task::Priority::Task_Priority_LOW);
    t1.set_allocated_due_date(new google::protobuf::Timestamp(google::protobuf::util::TimeUtil::TimeTToTimestamp(time(0))));
    Task t2;
    t2.set_title("task2");
    t2.set_priority(Task::Priority::Task_Priority_MEDIUM);
    t2.set_allocated_due_date(new google::protobuf::Timestamp(google::protobuf::util::TimeUtil::TimeTToTimestamp(time(0))));
    Task t3;
    t3.set_title("subtask");
    t3.set_priority(Task::Priority::Task_Priority_MEDIUM);
    t3.set_allocated_due_date(new google::protobuf::Timestamp(google::protobuf::util::TimeUtil::TimeTToTimestamp(time(0))));
    const std::pair<TaskId, Task> task1 = std::make_pair(parent_task_id, t1);
    const std::pair<TaskId, Task> task2 = std::make_pair(task2_id, t2);
    const std::pair<TaskId, Task> subtask = std::make_pair(task3_id, t3);
    AddExpectedPrint(PrintForm::WRITE_LINE, TaskToString(parent_task_id, t1));
    AddExpectedPrint(PrintForm::WRITE_LINE, "\t" + TaskToString(task3_id, t3));
    AddExpectedPrint(PrintForm::WRITE_LINE, TaskToString(task2_id, t2));
    TaskTransfer tt1;
    tt1.set_allocated_task_id(new TaskId(parent_task_id));
    tt1.set_allocated_task(new Task(t1));
    TaskTransfer tt2;
    tt2.set_allocated_task_id(new TaskId(task2_id));
    tt2.set_allocated_task(new Task(t2));
    TaskTransfer tt3;
    tt3.set_allocated_task_id(new TaskId(task3_id));
    tt3.set_allocated_task(new Task(t3));
    tt3.set_allocated_parent_id(new TaskId(parent_task_id));
    const std::vector<TaskTransfer> returned_tasks_from_controller { tt1, tt3, tt2 };
    std::shared_ptr<WizardStateInterface> expected_next_state = std::make_shared<RootState>(nullptr);
    // Assert
    EXPECT_CALL(*controller_, GetAllTasks()).Times(1).WillOnce(Return(returned_tasks_from_controller));
    EXPECT_CALL(*factory_, GetNextState(An<const ShowState&>(), WizardStatesFactory::MoveType::NEXT))
        .Times(1).WillOnce(Return(expected_next_state));
    // Act & Assert
    std::shared_ptr<WizardStateInterface> show_state = std::make_shared<ShowState>(std::move(dependencies_));
    ExecuteAndExpectReturn(show_state, expected_next_state);
}

TEST_F(StateTest, RootStateExecute_ShouldReturnNextStateFromFactory) {
    // Arrange
    const std::string expected_command = "help";
    AddExpectedRead("", expected_command);
    std::shared_ptr<WizardStateInterface> expected_next_state = std::make_shared<HelpState>(nullptr);
    // Assert
    EXPECT_CALL(*factory_, GetStateByCommand(expected_command))
        .Times(1).WillOnce(Return(expected_next_state));
    // Act & Assert
    std::shared_ptr<WizardStateInterface> root_state = std::make_shared<RootState>(std::move(dependencies_));
    ExecuteAndExpectReturn(root_state, expected_next_state);
}

TEST_F(StateTest, RootStateExecute_ShouldWriteErrorAndReturnRootStateOnWrongCommand) {
    // Arrange
    const std::string expected_command = "a";
    AddExpectedPrint(PrintForm::WRITE_ERROR, "Unknown command! Use help.");
    AddExpectedRead("", expected_command);
    std::shared_ptr<WizardStateInterface> expected_next_state = std::make_shared<RootState>(nullptr);
    // Assert
    EXPECT_CALL(*factory_, GetStateByCommand(expected_command))
            .Times(1).WillOnce(Return(nullptr));
    EXPECT_CALL(*factory_, GetNextState(An<const RootState&>(), WizardStatesFactory::MoveType::ERROR))
            .Times(1).WillOnce(Return(expected_next_state));
    // Act & Assert
    std::shared_ptr<WizardStateInterface> root_state = std::make_shared<RootState>(std::move(dependencies_));
    ExecuteAndExpectReturn(root_state, expected_next_state);
}

TEST_F(StateTest, QuitStateExecute_ShouldReturnNextStateOnPositiveInput) {
    // Arrange
    std::shared_ptr<WizardStateInterface> expected_next_state = std::make_shared<EndState>(nullptr);
    // Assert
    EXPECT_CALL(*dependencies_, UserConfirm("Are you sure?")).Times(1).WillOnce(Return(true));
    EXPECT_CALL(*factory_, GetNextState(An<const QuitState&>(), WizardStatesFactory::MoveType::NEXT))
            .Times(1).WillOnce(Return(expected_next_state));
    // Act & Assert
    std::shared_ptr<WizardStateInterface> quit_state = std::make_shared<QuitState>(std::move(dependencies_));
    ExecuteAndExpectReturn(quit_state, expected_next_state);
}

TEST_F(StateTest, QuitStateExecute_ShouldReturnPreviousStateOnNegativeResult) {
    // Arrange
    std::shared_ptr<WizardStateInterface> expected_next_state = std::make_shared<RootState>(nullptr);
    // Assert
    EXPECT_CALL(*dependencies_, UserConfirm("Are you sure?")).Times(1).WillOnce(Return(false));
    EXPECT_CALL(*factory_, GetNextState(An<const QuitState&>(), WizardStatesFactory::MoveType::PREVIOUS))
            .Times(1).WillOnce(Return(expected_next_state));
    // Act & Assert
    std::shared_ptr<WizardStateInterface> quit_state = std::make_shared<QuitState>(std::move(dependencies_));
    ExecuteAndExpectReturn(quit_state, expected_next_state);
}

TEST_F(StateTest, HelpState_ShouldPrintHelpMessage) {
    // Arrange
    AddExpectedPrint(PrintForm::WRITE_LINE, "Available commands:");
    AddExpectedPrint(PrintForm::WRITE_LINE, "1. add");
    AddExpectedPrint(PrintForm::WRITE_LINE, "2. add_subtask");
    AddExpectedPrint(PrintForm::WRITE_LINE, "3. edit");
    AddExpectedPrint(PrintForm::WRITE_LINE, "4. delete");
    AddExpectedPrint(PrintForm::WRITE_LINE, "5. complete");
    AddExpectedPrint(PrintForm::WRITE_LINE, "6. set_label");
    AddExpectedPrint(PrintForm::WRITE_LINE, "7. show");
    AddExpectedPrint(PrintForm::WRITE_LINE, "8. save");
    AddExpectedPrint(PrintForm::WRITE_LINE, "9. load");
    AddExpectedPrint(PrintForm::WRITE_LINE, "10. quit");
    std::shared_ptr<WizardStateInterface> expected_next_state = std::make_shared<RootState>(nullptr);
    // Assert
    EXPECT_CALL(*factory_, GetNextState(An<const HelpState&>(), WizardStatesFactory::MoveType::NEXT))
            .Times(1).WillOnce(Return(expected_next_state));
    // Act & Assert
    std::shared_ptr<WizardStateInterface> help_state = std::make_shared<HelpState>(std::move(dependencies_));
    ExecuteAndExpectReturn(help_state, expected_next_state);
}

TEST_F(StateTest, EndState_ShouldReturnNullptr) {
    // Arrange
    std::shared_ptr<WizardStateInterface> expected_next_state = nullptr;
    std::shared_ptr<WizardStateInterface> end_state = std::make_shared<EndState>(std::move(dependencies_));
    ExecuteAndExpectReturn(end_state, expected_next_state);
}

TEST_F(StateTest, DeleteTaskStateSuccess_ShouldAskControllerToDeleteTaskAndReturnPreviousState) {
    // Arrange
    std::shared_ptr<WizardStateInterface> expected_next_state = std::make_shared<RootState>(nullptr);
    const TaskId expected_deleted_task_id = StringToTaskId("10").value();
    // Assert
    AddExpectedReadId("Task ID", expected_deleted_task_id);
    EXPECT_CALL(*controller_, DeleteTask(expected_deleted_task_id))
        .Times(1).WillOnce(Return(TaskActionResult::SUCCESS));
    AddExpectedPrint(PrintForm::WRITE_LINE, "Task was successfully deleted.");
    EXPECT_CALL(*factory_, GetNextState(testing::An<const DeleteTaskState&>(), WizardStatesFactory::MoveType::PREVIOUS))
        .Times(1).WillOnce(Return(expected_next_state));
    // Act & Assert
    std::shared_ptr<WizardStateInterface> delete_state = std::make_shared<DeleteTaskState>(std::move(dependencies_));
    ExecuteAndExpectReturn(delete_state, expected_next_state);
}