//
// Created by Maksym Kharchenko on 13.01.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "view/ViewController.h"

#include "utilities/TaskComparators.h"

#include "mocks/MockController.h"
#include "mocks/MockCommand.h"
#include "mocks/MockUserInterface.h"

using ::testing::Return;

class ViewControllerTests : public ::testing::Test {
public:
    std::unique_ptr<MockController> controller;
    std::unique_ptr<MockUserInterface> user_interface;
    std::shared_ptr<MockCommand> command;
    void SetExpectedCommandResult (const CommandResult& command_result) {
        controller = std::make_unique<MockController>();
        user_interface = std::make_unique<MockUserInterface>();
        command = std::make_shared<MockCommand>();

        EXPECT_CALL(*user_interface, AskUserForAction()).WillOnce(Return(command)).WillOnce(Return(nullptr));
        EXPECT_CALL(*command, Execute(testing::NotNull())).WillOnce(Return(command_result));
    }
};

TEST_F(ViewControllerTests, RunUserInterface_ShouldAskUserInterfaceToPrintResult) {
    // Arrange
    const CommandResult expected_command_result = CommandResult::Create(ControllerRequestResult::SUCCESS);
    SetExpectedCommandResult(expected_command_result);

    EXPECT_CALL(*user_interface, PrintRequestResult(expected_command_result.GetResult())).Times(1);

    ViewController view_controller { std::move(controller), std::move(user_interface) };
    // Act
    view_controller.RunUserInterface();
}

TEST_F(ViewControllerTests, RunUserInterface_ShouldAskUIToPrintAddedTaskId) {
    // Arrange
    TaskId expected_task_id;
    expected_task_id.set_id(10);
    const CommandResult expected_command_result = CommandResult::Create(expected_task_id);
    SetExpectedCommandResult(expected_command_result);

    EXPECT_CALL(*user_interface, PrintAddedTaskId(expected_task_id)).Times(1);

    ViewController view_controller { std::move(controller), std::move(user_interface) };
    // Act
    view_controller.RunUserInterface();
}

TEST_F(ViewControllerTests, RunUserInterface_ShouldAskUIToShowTasks) {
    // Arrange
    RelationalTask tt;
    TaskId task_id;
    task_id.set_id(52);
    tt.set_allocated_task_id(new TaskId(task_id));
    tt.set_allocated_task(new Task(TaskBuilder::Create().SetTitle("title").BuildTask()));
    std::vector<RelationalTask> expected_show_tasks {tt };

    const CommandResult expected_command_result = CommandResult::Create(expected_show_tasks);
    SetExpectedCommandResult(expected_command_result);
    EXPECT_CALL(*user_interface, ShowTasks(expected_show_tasks)).Times(1);

    ViewController view_controller { std::move(controller), std::move(user_interface) };
    // Act
    view_controller.RunUserInterface();
}
