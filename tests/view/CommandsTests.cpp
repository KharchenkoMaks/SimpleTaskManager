//
// Created by Maksym Kharchenko on 11.01.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Task.pb.h"

#include "utilities/TaskBuilder.h"
#include "utilities/TaskComparators.h"
#include <google/protobuf/util/time_util.h>

#include "mocks/MockController.h"

#include "view/commands/CommandInterface.h"
#include "view/commands/AddSubTaskCommand.h"
#include "view/commands/AddTaskCommand.h"
#include "view/commands/CompleteTaskCommand.h"
#include "view/commands/DeleteTaskCommand.h"

#include <ctime>
#include <utility>

using ::testing::Return;

class CommandsTests : public ::testing::Test {
public:
    std::shared_ptr<MockController> controller_;
    void SetUp() override {
        controller_ = std::make_shared<MockController>();
    }
};

TEST_F(CommandsTests, AddSubTaskCommandExecuteSuccess_ShouldReturnTaskId) {
    // Arrange
    Task subtask = TaskBuilder::Create()
            .SetTitle("SubTask")
            .SetPriority(Task::Priority::Task_Priority_NONE)
            .SetDueDate(google::protobuf::util::TimeUtil::TimeTToTimestamp(time(0))).BuildTask();
    TaskId parent_id;
    parent_id.set_id(10);

    TaskId subtask_id;
    subtask_id.set_id(42);

    std::pair<ControllerRequestResult, TaskId> expected_return_from_controller = std::make_pair(ControllerRequestResult::SUCCESS, subtask_id);

    AddSubTaskCommand add_subtask_command(subtask, parent_id);
    // Assert
    EXPECT_CALL(*controller_, AddSubTask(subtask, parent_id)).WillOnce(Return(expected_return_from_controller));
    // Act
    CommandResult actual_result = add_subtask_command.Execute(controller_);
    // Assert
    EXPECT_EQ(ControllerRequestResult::SUCCESS, actual_result.GetResult());
    EXPECT_EQ(subtask_id, actual_result.GetTaskId());
}

TEST_F(CommandsTests, AddSubTaskCommandExecuteError_ShouldReturnErrorType) {
    // Arrange
    AddSubTaskCommand add_subtask_command(Task::default_instance(), TaskId::default_instance());
    std::pair<ControllerRequestResult, TaskId> expected_return_from_controller = std::make_pair(ControllerRequestResult::FAIL_NO_SUCH_TASK, TaskId::default_instance());
    // Assert
    EXPECT_CALL(*controller_, AddSubTask(Task::default_instance(), TaskId::default_instance())).WillOnce(Return(expected_return_from_controller));
    // Act
    CommandResult actual_result = add_subtask_command.Execute(controller_);
    // Assert
    EXPECT_EQ(ControllerRequestResult::FAIL_NO_SUCH_TASK, actual_result.GetResult());
}

TEST_F(CommandsTests, AddTaskCommandExecuteSuccess_ShouldReturnTaskId) {
    // Arrange
    Task task = TaskBuilder::Create()
            .SetTitle("SubTask")
            .SetPriority(Task::Priority::Task_Priority_NONE)
            .SetDueDate(google::protobuf::util::TimeUtil::TimeTToTimestamp(time(0))).BuildTask();

    TaskId task_id;
    task_id.set_id(42);

    const std::pair<ControllerRequestResult, TaskId> expected_return_from_controller = std::make_pair(ControllerRequestResult::SUCCESS, task_id);

    AddTaskCommand add_task_command(task);
    // Assert
    EXPECT_CALL(*controller_, AddTask(task)).WillOnce(Return(expected_return_from_controller));
    // Act
    CommandResult actual_result = add_task_command.Execute(controller_);
    // Assert
    EXPECT_EQ(ControllerRequestResult::SUCCESS, actual_result.GetResult());
    EXPECT_EQ(task_id, actual_result.GetTaskId());
}

TEST_F(CommandsTests, AddTaskCommandExecuteError_ShouldReturnErrorType) {
    // Arrange
    AddTaskCommand add_task_command(Task::default_instance());
    const std::pair<ControllerRequestResult, TaskId> expected_return_from_controller = std::make_pair(ControllerRequestResult::FAIL_NO_SUCH_TASK, TaskId::default_instance());
    // Assert
    EXPECT_CALL(*controller_, AddTask(Task::default_instance())).WillOnce(Return(expected_return_from_controller));
    // Act
    CommandResult actual_result = add_task_command.Execute(controller_);
    // Assert
    EXPECT_EQ(ControllerRequestResult::FAIL_NO_SUCH_TASK, actual_result.GetResult());
}

TEST_F(CommandsTests, CompleteTaskCommandExecuteForceCompleteSubTasks_ShouldCallForceCompleteTask) {
    // Arrange
    TaskId task_id;
    task_id.set_id(42);
    const bool force_complete = true;
    CompleteTaskCommand complete_task_command(task_id, force_complete);
    const ControllerRequestResult expected_result = ControllerRequestResult::SUCCESS;
    // Assert
    EXPECT_CALL(*controller_, CompleteTaskWithSubTasks(task_id)).WillOnce(Return(expected_result));
    // Act
    CommandResult actual_result = complete_task_command.Execute(controller_);
    // Assert
    EXPECT_EQ(expected_result, actual_result.GetResult());
}

TEST_F(CommandsTests, CompleteTaskCommandExecuteNoForceComplete_ShouldCallCompleteTask) {
    // Arrange
    TaskId task_id;
    task_id.set_id(42);
    const bool force_complete = false;
    CompleteTaskCommand complete_task_command(task_id, force_complete);
    const ControllerRequestResult expected_result = ControllerRequestResult::FAIL_UNCOMPLETED_SUBTASKS;
    // Assert
    EXPECT_CALL(*controller_, CompleteTask(task_id)).WillOnce(Return(expected_result));
    // Act
    CommandResult actual_result = complete_task_command.Execute(controller_);
    // Assert
    EXPECT_EQ(expected_result, actual_result.GetResult());
}

TEST_F(CommandsTests, DeleteTaskCommandExecuteForceDeleteSubTasks_ShouldCallForceDeleteTask) {
    // Arrange
    TaskId task_id;
    task_id.set_id(42);
    const bool force_delete = true;
    DeleteTaskCommand delete_task_command(task_id, force_delete);
    const ControllerRequestResult expected_result = ControllerRequestResult::SUCCESS;
    // Assert
    EXPECT_CALL(*controller_, DeleteTaskWithSubTasks(task_id)).WillOnce(Return(expected_result));
    // Act
    CommandResult actual_result = delete_task_command.Execute(controller_);
    // Assert
    EXPECT_EQ(expected_result, actual_result.GetResult());
}

TEST_F(CommandsTests, DeleteTaskCommandExecuteNoForceComplete_ShouldCallDeleteTask) {
    // Arrange
    TaskId task_id;
    task_id.set_id(42);
    const bool force_delete = false;
    DeleteTaskCommand delete_task_command(task_id, force_delete);
    const ControllerRequestResult expected_result = ControllerRequestResult::FAIL_NO_SUCH_TASK;
    // Assert
    EXPECT_CALL(*controller_, DeleteTask(task_id)).WillOnce(Return(expected_result));
    // Act
    CommandResult actual_result = delete_task_command.Execute(controller_);
    // Assert
    EXPECT_EQ(expected_result, actual_result.GetResult());
}