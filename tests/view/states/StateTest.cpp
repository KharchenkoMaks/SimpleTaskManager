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
    void AddExpectedRead(const std::string& invitation_message, const std::string& return_string) {
        EXPECT_CALL(*dependencies_, GetUserInput(invitation_message))
                .Times(1)
                .WillOnce(Return(return_string));
    }
};

TEST_F(StateTest, ShowStateExecute_ShouldPrintTasksReceivedFromController) {
    // Arrange
    const TaskId parent_task_id = TaskId::Create(0).value();
    const std::pair<TaskId, Task> task1 = std::make_pair(parent_task_id, Task::Create("task1", Task::Priority::LOW, DueTime::Create(100)));
    const std::pair<TaskId, Task> task2 = std::make_pair(TaskId::Create(1).value(), Task::Create("task2", Task::Priority::MEDIUM, DueTime::Create(100)));
    const std::pair<TaskId, Task> subtask = std::make_pair(TaskId::Create(1).value(), Task::Create("subtask", Task::Priority::MEDIUM, DueTime::Create(100)));
    AddExpectedPrint(PrintForm::WRITE_LINE, task1.first.to_string() + ", " + task1.second.to_string());
    AddExpectedPrint(PrintForm::WRITE_LINE, "\t" + subtask.first.to_string() + ", " + subtask.second.to_string());
    AddExpectedPrint(PrintForm::WRITE_LINE, task2.first.to_string() + ", " + task2.second.to_string());
    const std::vector<TaskTransfer> returned_tasks_from_controller {
            TaskTransfer::Create(task1.first, task1.second),
            TaskTransfer::Create(subtask.first, subtask.second, parent_task_id),
            TaskTransfer::Create(task2.first, task2.second)
    };
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