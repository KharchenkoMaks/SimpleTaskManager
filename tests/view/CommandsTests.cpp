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

#include "view/commands/Command.h"
#include "view/commands/AddSubTaskCommand.h"
#include "view/commands/AddTaskCommand.h"
#include "view/commands/CompleteTaskCommand.h"
#include "view/commands/DeleteTaskCommand.h"
#include "view/commands/EditTaskCommand.h"
#include "view/commands/LoadCommand.h"
#include "view/commands/SaveCommand.h"
#include "view/commands/SetLabelCommand.h"
#include "view/commands/ShowTasksCommand.h"
#include "view/commands/RemoveLabelCommand.h"

#include "view/commands/CommandResult.h"

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

TEST_F(CommandsTests, EditTaskCommandExecute_ShouldMergeAndEditTask) {
    // Arrange
    TaskBuilder edited_task = TaskBuilder::Create().SetTitle("new title");
    TaskId task_id;
    task_id.set_id(42);
    Task task_to_edit = TaskBuilder::Create()
            .SetTitle("old title")
            .SetPriority(Task::Priority::Task_Priority_LOW)
            .SetDueDate(google::protobuf::util::TimeUtil::TimeTToTimestamp(time(0)))
            .BuildTask();
    Task expected_edited_task = edited_task.Merge(task_to_edit).BuildTask();
    RelationalTask returned_task_from_controller;
    returned_task_from_controller.set_allocated_task(new Task(expected_edited_task));
    EditTaskCommand edit_task_command(edited_task, task_id);
    const ControllerRequestResult expected_result = ControllerRequestResult::SUCCESS;
    // Assert
    EXPECT_CALL(*controller_, GetTask(task_id)).WillOnce(Return(returned_task_from_controller));
    EXPECT_CALL(*controller_, EditTask(task_id, expected_edited_task)).WillOnce(Return(expected_result));
    // Act
    CommandResult actual_result = edit_task_command.Execute(controller_);
    // Assert
    EXPECT_EQ(expected_result, actual_result.GetResult());
}

TEST_F(CommandsTests, EditTaskCommandExecuteWithNonExistentTask_ShouldReturnNoSuchTask) {
    // Arrange
    TaskId task_id;
    task_id.set_id(100);
    EditTaskCommand edit_task_command(TaskBuilder::Create(), task_id);
    const ControllerRequestResult expected_result = ControllerRequestResult::FAIL_NO_SUCH_TASK;
    // Assert
    EXPECT_CALL(*controller_, GetTask(task_id)).WillOnce(Return(std::nullopt));
    // Act
    CommandResult actual_result = edit_task_command.Execute(controller_);
    // Assert
    EXPECT_EQ(expected_result, actual_result.GetResult());
}

TEST_F(CommandsTests, LoadCommandExecute_ShouldCallLoadFromController) {
    // Arrange
    const std::string file_name = "file name";
    LoadCommand load_command(file_name);
    const ControllerRequestResult expected_result = ControllerRequestResult::FILE_DAMAGED;
    // Assert
    EXPECT_CALL(*controller_, LoadFromFile(file_name)).WillOnce(Return(expected_result));
    // Act
    CommandResult actual_result = load_command.Execute(controller_);
    // Assert
    EXPECT_EQ(expected_result, actual_result.GetResult());
}

TEST_F(CommandsTests, SaveCommandExecute_ShouldCallSaveFromController) {
    // Arrange
    const std::string file_name = "file name";
    SaveCommand save_command(file_name);
    const ControllerRequestResult expected_result = ControllerRequestResult::SUCCESS;
    // Assert
    EXPECT_CALL(*controller_, SaveToFile(file_name)).WillOnce(Return(expected_result));
    // Act
    CommandResult actual_result = save_command.Execute(controller_);
    // Assert
    EXPECT_EQ(expected_result, actual_result.GetResult());
}

TEST_F(CommandsTests, SetLabelCommandExecute_ShouldSetLabelInController) {
    // Arrange
    const std::string label = "some label";
    TaskId task_id;
    task_id.set_id(9);
    SetLabelCommand set_label_command(task_id, label);
    const ControllerRequestResult expected_result = ControllerRequestResult::SUCCESS;
    // Assert
    EXPECT_CALL(*controller_, AddTaskLabel(task_id, label)).WillOnce(Return(expected_result));
    // Act
    CommandResult actual_result = set_label_command.Execute(controller_);
    // Assert
    EXPECT_EQ(expected_result, actual_result.GetResult());
}

TEST_F(CommandsTests, RemoveLabelCommandExecute_ShouldRemoveLabelInController) {
    // Arrange
    const std::string label = "some label";
    TaskId task_id;
    task_id.set_id(9);
    RemoveLabelCommand remove_label_command(task_id, label);
    const ControllerRequestResult expected_result = ControllerRequestResult::SUCCESS;
    // Assert
    EXPECT_CALL(*controller_, RemoveTaskLabel(task_id, label)).WillOnce(Return(expected_result));
    // Act
    CommandResult actual_result = remove_label_command.Execute(controller_);
    // Assert
    EXPECT_EQ(expected_result, actual_result.GetResult());
}

TEST_F(CommandsTests, ShowTasksCommandExecute_ShouldFetchAllTasksFromControllerAndReturnThem) {
    // Arrange
    ShowTasksCommand show_tasks_command { "" };
    const ControllerRequestResult expected_result = ControllerRequestResult::SUCCESS;
    // Arrange tasks to show
    TaskId parent_task_id;
    TaskId task2_id;
    task2_id.set_id(2);
    TaskId task3_id;
    task3_id.set_id(3);
    Task t1 = TaskBuilder::Create()
            .SetTitle("task1").SetPriority(Task::Priority::Task_Priority_LOW).SetDueDate(google::protobuf::util::TimeUtil::TimeTToTimestamp(time(0))).BuildTask();
    Task t2 = TaskBuilder::Create()
            .SetTitle("task2").SetPriority(Task::Priority::Task_Priority_MEDIUM).SetDueDate(google::protobuf::util::TimeUtil::TimeTToTimestamp(time(0))).BuildTask();
    Task t3 = TaskBuilder::Create()
            .SetTitle("subtask").SetPriority(Task::Priority::Task_Priority_MEDIUM).SetDueDate(google::protobuf::util::TimeUtil::TimeTToTimestamp(time(0))).BuildTask();
    RelationalTask tt1;
    tt1.set_allocated_task_id(new TaskId(parent_task_id));
    tt1.set_allocated_task(new Task(t1));
    RelationalTask tt2;
    tt2.set_allocated_task_id(new TaskId(task2_id));
    tt2.set_allocated_task(new Task(t2));
    RelationalTask tt3;
    tt3.set_allocated_task_id(new TaskId(task3_id));
    tt3.set_allocated_task(new Task(t3));
    tt3.set_allocated_parent_id(new TaskId(parent_task_id));

    std::vector<RelationalTask> tasks { tt1, tt3, tt2 };
    const CommandResult::TasksToShow expected_tasks_to_show { tasks, true };

    // Assert
    EXPECT_CALL(*controller_, GetAllTasks()).WillOnce(Return(tasks));
    // Act
    CommandResult actual_result = show_tasks_command.Execute(controller_);
    // Assert
    EXPECT_EQ(expected_result, actual_result.GetResult());
    EXPECT_EQ(expected_tasks_to_show, actual_result.GetTasksToShow());
}