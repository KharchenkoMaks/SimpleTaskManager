//
// Created by Maksym Kharchenko on 14.11.2021.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "TaskManager.h"
#include "IdGenerator.h"
#include "Task.pb.h"
#include "TaskNode.pb.h"
#include "utilities/TaskActionResult.h"
#include "utilities/TaskComparators.h"
#include "../utilities/MockTaskValidator.h"

#include <ctime>
#include <string>
#include <vector>
#include <utility>
#include <optional>
#include <google/protobuf/util/time_util.h>

using ::testing::Return;

class MockIdGenerator : public IdGenerator{
public:
    MOCK_METHOD(TaskId, CreateNewTaskId, (), (override));
    MOCK_METHOD(void, SetLastTaskId, (const TaskId& task_id), (override));
};

class TaskManagerTest : public ::testing::Test {
public:
    google::protobuf::Timestamp expected_time;
    std::string expected_title[3] = { "task1", "task2", "task3" };
    Task::Priority expected_priority[3] =
            { Task::Priority::Task_Priority_NONE,
              Task::Priority::Task_Priority_LOW,
              Task::Priority::Task_Priority_MEDIUM};
    TaskId expected_first_task_id;
    TaskId expected_second_task_id;
    TaskId expected_third_task_id;
    Task expected_first_task;
    Task expected_second_task;
    Task expected_third_task;
    void SetUp() override {
        expected_time = google::protobuf::util::TimeUtil::TimeTToTimestamp(1702737566);

        expected_first_task_id.set_id(1);
        expected_second_task_id.set_id(2);
        expected_third_task_id.set_id(5);

        expected_first_task.set_title(expected_title[0]);
        expected_first_task.set_priority(expected_priority[0]);
        expected_first_task.set_allocated_due_date(new google::protobuf::Timestamp(expected_time));
        expected_second_task.set_title(expected_title[1]);
        expected_second_task.set_priority(expected_priority[1]);
        expected_second_task.set_allocated_due_date(new google::protobuf::Timestamp(expected_time));
        expected_third_task.set_title(expected_title[2]);
        expected_third_task.set_priority(expected_priority[2]);
        expected_third_task.set_allocated_due_date(new google::protobuf::Timestamp(expected_time));
    }
    std::vector<RelationalTask> FormTasksToVector() const {
        RelationalTask tt1;
        tt1.set_allocated_task(new Task(expected_first_task));
        tt1.set_allocated_task_id(new TaskId(expected_first_task_id));
        RelationalTask tt2;
        tt2.set_allocated_task(new Task(expected_second_task));
        tt2.set_allocated_task_id(new TaskId(expected_second_task_id));
        tt2.set_allocated_parent_id(new TaskId(expected_first_task_id));
        RelationalTask tt3;
        tt3.set_allocated_task(new Task(expected_third_task));
        tt3.set_allocated_task_id(new TaskId(expected_third_task_id));
        tt3.set_allocated_parent_id(new TaskId(expected_first_task_id));

        std::vector<RelationalTask> tasks {tt1, tt2, tt3 };
        return tasks;
    }
};

// Creating two Tasks in TaskManager
// Should return right Tasks in GetTasks() method
TEST_F(TaskManagerTest, CreatingTasks_ShouldReturnTaskVector){
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);

    EXPECT_CALL(*gen, CreateNewTaskId())
        .Times(2)
        .WillOnce(Return(expected_first_task_id))
        .WillOnce(Return(expected_second_task_id));

    TaskManager task_manager(std::move(gen));
    // Act
    TaskId task1 = task_manager.AddTask(expected_first_task).second;
    TaskId task2 = task_manager.AddTask(expected_second_task).second;

    std::vector<RelationalTask> tasks = task_manager.GetTasks();
    // Assert
    // Check size of task vector equals 2
    ASSERT_EQ(tasks.size(), 2);
    // Check equality of task1
    EXPECT_EQ(tasks[0].task_id(), expected_first_task_id);
    EXPECT_EQ(tasks[0].task().title(), expected_title[0]);
    EXPECT_EQ(tasks[0].task().priority(), expected_priority[0]);
    EXPECT_EQ(tasks[0].task().due_date(), expected_time);
    EXPECT_FALSE(tasks[0].has_parent_id());
    // Check equality of task2
    EXPECT_EQ(tasks[1].task_id(), expected_second_task_id);
    EXPECT_EQ(tasks[1].task().title(), expected_title[1]);
    EXPECT_EQ(tasks[1].task().priority(), expected_priority[1]);
    EXPECT_EQ(tasks[1].task().due_date(), expected_time);
    EXPECT_FALSE(tasks[1].has_parent_id());
}

// Editing existing Task in TaskManager
// Should return edited task
TEST_F(TaskManagerTest, EditingTask_ShouldReturnEditedTask){
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
        .Times(2)
        .WillOnce(Return(expected_first_task_id))
        .WillOnce(Return(expected_second_task_id));

    TaskManager task_manager(std::move(gen));
    const std::string expected_title = "edited task";
    const Task::Priority expected_priority = Task::Priority::Task_Priority_HIGH;
    Task edited_task;
    edited_task.set_title(expected_title);
    edited_task.set_priority(expected_priority);
    edited_task.set_allocated_due_date(new google::protobuf::Timestamp(expected_time));

    TaskId main_task_id = task_manager.AddTask(expected_first_task).second;
    TaskId subtask_id = task_manager.AddSubTask(expected_second_task, main_task_id).second;
    // Act
    task_manager.EditTask(main_task_id, edited_task);
    task_manager.EditTask(subtask_id, edited_task);
    std::optional<RelationalTask> actual_main = task_manager.GetTask(main_task_id);
    std::optional<RelationalTask> actual_sub = task_manager.GetTask(subtask_id);
    // Assert
    ASSERT_NE(actual_main, std::nullopt);
    ASSERT_NE(actual_sub, std::nullopt);

    EXPECT_EQ(expected_first_task_id, actual_main.value().task_id());
    EXPECT_EQ(expected_title, actual_main.value().task().title());
    EXPECT_EQ(expected_priority, actual_main.value().task().priority());
    EXPECT_EQ(expected_time, actual_main.value().task().due_date());
    EXPECT_FALSE(actual_main.value().has_parent_id());

    EXPECT_EQ(expected_second_task_id, actual_sub.value().task_id());
    EXPECT_EQ(expected_title, actual_sub.value().task().title());
    EXPECT_EQ(expected_priority, actual_sub.value().task().priority());
    EXPECT_EQ(expected_time, actual_sub.value().task().due_date());
    EXPECT_EQ(actual_sub.value().parent_id(), main_task_id);
}

// Creating two Tasks in TaskManager
// Deleting first task
// GetTasks method should return only second task
TEST_F(TaskManagerTest, DeleteTask_ShouldDeleteTaskProperly){
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
        .Times(2)
        .WillOnce(Return(expected_first_task_id))
        .WillOnce(Return(expected_second_task_id));

    TaskManager task_manager(std::move(gen));
    TaskId task_id_1 = task_manager.AddTask(expected_first_task).second;
    TaskId task_id_2 = task_manager.AddTask(expected_second_task).second;
    // Act
    task_manager.DeleteTask(task_id_1, false);
    std::vector<RelationalTask> tasks = task_manager.GetTasks();
    TaskId actual_task_id = tasks[0].task_id();
    Task actual_task = tasks[0].task();
    // Assert
    ASSERT_TRUE(tasks.size() == 1);
    EXPECT_EQ(actual_task_id, expected_second_task_id);
    EXPECT_EQ(actual_task.title(), expected_title[1]);
    EXPECT_EQ(actual_task.priority(), expected_priority[1]);
    EXPECT_EQ(actual_task.due_date(), expected_time);
}

// Giving unused TaskId to EditTask() method
// Should return false
TEST_F(TaskManagerTest, TryEditingNonExistentTask_ShouldReturnFalse){
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
        .Times(0);

    TaskManager task_manager(std::move(gen));
    // Act & Assert
    EXPECT_EQ(task_manager.EditTask(expected_first_task_id, expected_first_task), TaskActionResult::FAIL_NO_SUCH_TASK);
}

// Giving unused TaskId to DeleteTask method
// Should return false
TEST_F(TaskManagerTest, TryDeletingNonExistentTask_ShouldReturnFalse){
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
        .Times(0);

    TaskManager task_manager(std::move(gen));
    // Act & Assert
    EXPECT_EQ(task_manager.DeleteTask(expected_first_task_id, false), TaskActionResult::FAIL_NO_SUCH_TASK);
}

// Creating three Tasks
// Completing first and third task
// First and third Tasks should be completed
TEST_F(TaskManagerTest, TryCompletingDifferentTasks_ShouldCompleteThoseTasks){
    // Arrange

    TaskManager task_manager(std::make_unique<IdGenerator>());

    const std::string expected_not_completed_title = "i am not completed";
    Task expected_not_completed_task;
    expected_not_completed_task.set_title(expected_not_completed_title);
    expected_not_completed_task.set_priority(Task::Priority::Task_Priority_HIGH);
    expected_not_completed_task.set_allocated_due_date(new google::protobuf::Timestamp(expected_time));

    TaskId task1 = task_manager.AddTask(expected_first_task).second;
    TaskId task2 = task_manager.AddTask(expected_not_completed_task).second;
    TaskId task3 = task_manager.AddTask(expected_second_task).second;
    // Act
    task_manager.CompleteTask(task1, false);
    task_manager.CompleteTask(task3, false);
    std::vector<RelationalTask> tasks = task_manager.GetTasks();
    Task actual_first_completed_task = tasks[0].task();
    Task actual_second_completed_task = tasks[2].task();
    Task actual_not_completed_task = tasks[1].task();
    // Assert
    ASSERT_EQ(tasks.size(), 3);

    EXPECT_EQ(actual_first_completed_task.title(), expected_title[0]);
    EXPECT_TRUE(actual_first_completed_task.completed());
    EXPECT_EQ(actual_second_completed_task.title(), expected_title[1]);
    EXPECT_TRUE(actual_second_completed_task.completed());
    EXPECT_EQ(actual_not_completed_task.title(), expected_not_completed_title);
    EXPECT_FALSE(actual_not_completed_task.completed());
}

// Trying to complete non-existent TaskId
// Should return false
TEST_F(TaskManagerTest, TryCompletingNonExistentTask_ShouldReturnFalse){
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
            .Times(0);

    TaskManager task_manager(std::move(gen));
    // Act & Assert
    EXPECT_EQ(task_manager.CompleteTask(expected_first_task_id, false), TaskActionResult::FAIL_NO_SUCH_TASK);
}

// Adding subtask to task manager
// GetTask should return right subtask
TEST_F(TaskManagerTest, TryAddingSubtask_ShouldReturnRightTask) {
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
            .Times(2)
            .WillOnce(Return(expected_first_task_id))
            .WillOnce(Return(expected_second_task_id));

    TaskManager task_manager(std::move(gen));

    // Act
    TaskId main_task_id = task_manager.AddTask(expected_first_task).second;
    TaskId subtask_id = task_manager.AddSubTask(expected_second_task, main_task_id).second;
    std::optional<RelationalTask> get_subtask = task_manager.GetTask(subtask_id);
    // Assert
    ASSERT_NE(get_subtask, std::nullopt);
    EXPECT_EQ(get_subtask.value().task_id(), subtask_id);
    EXPECT_EQ(get_subtask.value().parent_id(), main_task_id);
    EXPECT_EQ(get_subtask.value().task(), expected_second_task);
    EXPECT_TRUE(task_manager.IsTaskExist(subtask_id));
    EXPECT_TRUE(task_manager.IsTaskExist(main_task_id));
}

TEST_F(TaskManagerTest, TryGetNonExistentTask_ShouldReturnNullopt) {
    // Arrange
    TaskManager task_manager(std::make_unique<IdGenerator>());
    // Act
    std::optional<RelationalTask> task = task_manager.GetTask(expected_first_task_id);
    // Assert
    EXPECT_EQ(task, std::nullopt);
}

TEST_F(TaskManagerTest, TryDeletingSubTask_ShouldDeleteSubTaskProperly) {
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
            .Times(3)
            .WillOnce(Return(expected_first_task_id))
            .WillOnce(Return(expected_second_task_id))
            .WillOnce(Return(expected_third_task_id));

    TaskManager task_manager(std::move(gen));

    TaskId main_task_id = task_manager.AddTask(expected_first_task).second;
    TaskId subtask1_id = task_manager.AddSubTask(expected_second_task, main_task_id).second;
    TaskId subtask2_id = task_manager.AddSubTask(expected_third_task, main_task_id).second;

    // Act
    task_manager.DeleteTask(subtask1_id, false);
    const std::vector<RelationalTask> tasks = task_manager.GetTasks();
    const RelationalTask main_task_transfer = tasks[0];
    const RelationalTask subtask_transfer = tasks[1];

    // Assert
    ASSERT_EQ(tasks.size(), 2);

    EXPECT_EQ(main_task_transfer.task(), expected_first_task);
    EXPECT_EQ(main_task_transfer.task_id(), main_task_id);
    EXPECT_FALSE(main_task_transfer.has_parent_id());

    EXPECT_EQ(subtask_transfer.task(), expected_third_task);
    EXPECT_EQ(subtask_transfer.task_id(), subtask2_id);
    EXPECT_EQ(subtask_transfer.parent_id(), main_task_id);
}

TEST_F(TaskManagerTest, TryCompleteSubTask_ShouldCompleteSubTask) {
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
            .Times(3)
            .WillOnce(Return(expected_first_task_id))
            .WillOnce(Return(expected_second_task_id))
            .WillOnce(Return(expected_third_task_id));

    TaskManager task_manager(std::move(gen));

    TaskId main_task_id = task_manager.AddTask(expected_first_task).second;
    TaskId subtask1_id = task_manager.AddSubTask(expected_second_task, main_task_id).second;
    TaskId subtask2_id = task_manager.AddSubTask(expected_third_task, main_task_id).second;

    // Act
    task_manager.CompleteTask(subtask1_id, false);
    const std::optional<RelationalTask> actual_subtask = task_manager.GetTask(subtask1_id);
    // Assert
    ASSERT_NE(actual_subtask, std::nullopt);
    EXPECT_TRUE(actual_subtask->task().completed());
}

TEST_F(TaskManagerTest, AddTaskLabel_ShouldAddLabelsToDifferentTasksProperly) {
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
            .WillOnce(Return(expected_first_task_id))
            .WillOnce(Return(expected_second_task_id));

    TaskManager task_manager(std::move(gen));
    TaskId main_task_id = task_manager.AddTask(expected_first_task).second;
    TaskId subtask_id = task_manager.AddSubTask(expected_second_task, main_task_id).second;
    std::string expected_main_task_label1 = "main task label";
    std::string expected_main_task_label2 = "label2";
    std::string expected_subtask_label = "subtask label";
    // Act
    TaskActionResult actual_main_task_result1 = task_manager.AddTaskLabel(main_task_id, expected_main_task_label1);
    TaskActionResult actual_main_task_result2 = task_manager.AddTaskLabel(main_task_id, expected_main_task_label2);
    TaskActionResult actual_subtask_result = task_manager.AddTaskLabel(subtask_id, expected_subtask_label);
    Task actual_main_task = task_manager.GetTask(main_task_id).value().task();
    Task actual_subtask = task_manager.GetTask(subtask_id).value().task();
    // ASSERT
    ASSERT_EQ(TaskActionResult::SUCCESS, actual_main_task_result1);
    ASSERT_EQ(TaskActionResult::SUCCESS, actual_main_task_result2);
    ASSERT_EQ(TaskActionResult::SUCCESS, actual_subtask_result);
    ASSERT_EQ(2, actual_main_task.label_size());
    ASSERT_EQ(1, actual_subtask.label_size());
    EXPECT_EQ(expected_main_task_label1, actual_main_task.label(0));
    EXPECT_EQ(expected_main_task_label2, actual_main_task.label(1));
    EXPECT_EQ(expected_subtask_label, actual_subtask.label(0));
}

TEST_F(TaskManagerTest, AddTaskLabel_TryAddEmptyLabel_ShouldReturnError) {
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId()).Times(0);
    TaskManager task_manager(std::move(gen));
    const std::string expected_label = "";
    const TaskActionResult expected_result = TaskActionResult::FAIL_INVALID_LABEL;
    // Act
    TaskActionResult actual_result = task_manager.AddTaskLabel(TaskId::default_instance(), expected_label);
    // Assert
    EXPECT_EQ(expected_result, actual_result);
}

TEST_F(TaskManagerTest, AddTaskLabel_TryAddLabelForNonExistentTask_ShouldReturnError) {
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId()).Times(0);
    TaskManager task_manager(std::move(gen));
    const TaskActionResult expected_result = TaskActionResult::FAIL_NO_SUCH_TASK;
    // Act
    TaskActionResult actual_result = task_manager.AddTaskLabel(TaskId::default_instance(), "label");
    // Assert
    EXPECT_EQ(expected_result, actual_result);
}

TEST_F(TaskManagerTest, AddTaskLabel_TryAddSameLabel_ShouldReturnError) {
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
            .WillOnce(Return(expected_first_task_id));

    TaskManager task_manager(std::move(gen));
    TaskId main_task_id = task_manager.AddTask(expected_first_task).second;
    std::string expected_main_task_label = "main task label";
    // Act
    TaskActionResult actual_main_task_first_result = task_manager.AddTaskLabel(main_task_id, expected_main_task_label);
    // adding same label for second time, should return fail
    TaskActionResult actual_main_task_second_result = task_manager.AddTaskLabel(main_task_id, expected_main_task_label);
    Task actual_main_task = task_manager.GetTask(main_task_id).value().task();
    // ASSERT
    ASSERT_EQ(TaskActionResult::SUCCESS, actual_main_task_first_result);
    ASSERT_EQ(TaskActionResult::FAIL_LABEL_ALREADY_SET, actual_main_task_second_result);
    ASSERT_EQ(1, actual_main_task.label_size());
    EXPECT_EQ(expected_main_task_label, actual_main_task.label(0));
}

TEST_F(TaskManagerTest, RemoveTaskLabel_ShouldRemoveLabelFromTask) {
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
            .WillOnce(Return(expected_first_task_id));

    TaskManager task_manager(std::move(gen));

    const std::string expected_label_to_be_left = "first label";
    const std::string expected_label_to_be_removed = "second label";
    const TaskActionResult expected_result = TaskActionResult::SUCCESS;

    expected_first_task.add_label(expected_label_to_be_left);
    expected_first_task.add_label(expected_label_to_be_removed);
    task_manager.AddTask(expected_first_task);
    // Act
    const TaskActionResult actual_result = task_manager.RemoveTaskLabel(expected_first_task_id, expected_label_to_be_removed);
    Task actual_task = task_manager.GetTask(expected_first_task_id).value().task();
    // Assert
    ASSERT_EQ(expected_result, actual_result);
    ASSERT_EQ(1, actual_task.label_size());
    EXPECT_EQ(expected_label_to_be_left, actual_task.label(0));
}

TEST_F(TaskManagerTest, RemoveTaskLabel_TryToRemoveLabelFromNonExistentTask_ShouldReturnError) {
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId()).Times(0);
    TaskManager task_manager(std::move(gen));
    const TaskActionResult expected_result = TaskActionResult::FAIL_NO_SUCH_TASK;
    // Act
    TaskActionResult actual_result = task_manager.RemoveTaskLabel(TaskId::default_instance(), "label");
    // Assert
    EXPECT_EQ(expected_result, actual_result);
}

TEST_F(TaskManagerTest, RemoveTaskLabel_TryToRemoveNotAssignedLabel_ShouldReturnError) {
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
            .WillOnce(Return(expected_first_task_id));

    TaskManager task_manager(std::move(gen));
    task_manager.AddTask(expected_first_task);

    const TaskActionResult expected_result = TaskActionResult::FAIL_NO_SUCH_LABEL;
    // Act
    const TaskActionResult actual_result = task_manager.RemoveTaskLabel(expected_first_task_id, "label");
    const Task actual_task = task_manager.GetTask(expected_first_task_id).value().task();
    // Assert
    ASSERT_EQ(expected_result, actual_result);
    EXPECT_EQ(0, actual_task.label_size());
}

TEST_F(TaskManagerTest, AddTask_TryAddInvalidTask_ShouldReturnError) {
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    std::unique_ptr<MockTaskValidator> task_validator = std::make_unique<MockTaskValidator>();
    EXPECT_CALL(*task_validator, ValidateTask(Task::default_instance())).Times(2).WillRepeatedly(Return(false));
    EXPECT_CALL(*gen, CreateNewTaskId()).Times(0);
    TaskManager task_manager(std::move(gen), std::move(task_validator));
    const TaskActionResult expected_error = TaskActionResult::FAIL_INVALID_TASK;
    // Act
    const auto actual_add_task_result = task_manager.AddTask(Task::default_instance());
    const auto actual_add_subtask_result = task_manager.AddSubTask(Task::default_instance(), TaskId::default_instance());
    // Assert
    EXPECT_EQ(expected_error, actual_add_task_result.first);
    EXPECT_EQ(TaskId::default_instance(), actual_add_task_result.second);
    EXPECT_EQ(expected_error, actual_add_subtask_result.first);
    EXPECT_EQ(TaskId::default_instance(), actual_add_subtask_result.second);
}

TEST_F(TaskManagerTest, EditTask_TryEditInvalidTask_ShouldReturnError) {
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    std::unique_ptr<MockTaskValidator> task_validator = std::make_unique<MockTaskValidator>();
    EXPECT_CALL(*task_validator, ValidateTask(Task::default_instance())).WillOnce(Return(false));
    EXPECT_CALL(*gen, CreateNewTaskId()).Times(0);
    TaskManager task_manager(std::move(gen), std::move(task_validator));
    const TaskActionResult expected_error = TaskActionResult::FAIL_INVALID_TASK;
    // Act
    const TaskActionResult actual_result = task_manager.EditTask(TaskId::default_instance(), Task::default_instance());
    // Assert
    EXPECT_EQ(expected_error, actual_result);
}

TEST_F(TaskManagerTest, AddSubTask_TryAddSubTaskForNonExistentParentTask_ShouldReturnError) {
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId()).Times(0);
    TaskManager task_manager(std::move(gen));
    const TaskActionResult expected_error = TaskActionResult::FAIL_NO_SUCH_TASK;
    // Act
    const auto actual_result = task_manager.AddSubTask(expected_first_task, TaskId::default_instance());
    // Assert
    EXPECT_EQ(expected_error, actual_result.first);
    EXPECT_EQ(TaskId::default_instance(), actual_result.second);
}

TEST_F(TaskManagerTest, DeleteTask_TryDeleteMainTaskWithNotDeletedSubtasks_ShouldReturnError) {
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
            .Times(3)
            .WillOnce(Return(expected_first_task_id))
            .WillOnce(Return(expected_second_task_id))
            .WillOnce(Return(expected_third_task_id));

    TaskManager task_manager(std::move(gen));

    TaskId main_task_id = task_manager.AddTask(expected_first_task).second;
    TaskId subtask1_id = task_manager.AddSubTask(expected_second_task, main_task_id).second;
    TaskId subtask2_id = task_manager.AddSubTask(expected_third_task, main_task_id).second;

    const TaskActionResult expected_result = TaskActionResult::FAIL_NOT_DELETED_SUBTASKS;
    // Act
    const TaskActionResult actual_result = task_manager.DeleteTask(main_task_id, false);
    // Assert
    EXPECT_EQ(expected_result, actual_result);
}

TEST_F(TaskManagerTest, CompleteTask_TryCompleteMainTaskWithNotCompletedSubtasks_ShouldReturnError) {
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
            .Times(3)
            .WillOnce(Return(expected_first_task_id))
            .WillOnce(Return(expected_second_task_id))
            .WillOnce(Return(expected_third_task_id));

    TaskManager task_manager(std::move(gen));

    TaskId main_task_id = task_manager.AddTask(expected_first_task).second;
    TaskId subtask1_id = task_manager.AddSubTask(expected_second_task, main_task_id).second;
    TaskId subtask2_id = task_manager.AddSubTask(expected_third_task, main_task_id).second;

    const TaskActionResult expected_result = TaskActionResult::FAIL_UNCOMPLETED_SUBTASKS;
    // Act
    const TaskActionResult actual_result = task_manager.CompleteTask(main_task_id, false);
    // Assert
    EXPECT_EQ(expected_result, actual_result);
}

TEST_F(TaskManagerTest, DeleteTask_TryDeleteMainTaskWithForceDeleteSubtasks_ShouldDeleteAllTasks) {
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
            .Times(3)
            .WillOnce(Return(expected_first_task_id))
            .WillOnce(Return(expected_second_task_id))
            .WillOnce(Return(expected_third_task_id));

    TaskManager task_manager(std::move(gen));

    TaskId main_task_id = task_manager.AddTask(expected_first_task).second;
    TaskId subtask1_id = task_manager.AddSubTask(expected_second_task, main_task_id).second;
    TaskId subtask2_id = task_manager.AddSubTask(expected_third_task, main_task_id).second;

    const TaskActionResult expected_result = TaskActionResult::SUCCESS;
    const size_t expected_tasks_size = 0;
    // Act
    const TaskActionResult actual_result = task_manager.DeleteTask(main_task_id, true);
    const auto actual_tasks_size = task_manager.GetTasks().size();
    // Assert
    ASSERT_EQ(expected_result, actual_result);
    EXPECT_EQ(expected_tasks_size, actual_tasks_size);
}

TEST_F(TaskManagerTest, CompleteTask_TryCompleteMainTaskWithForceCompleteSubtasks_ShouldCompleteAllTasks) {
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
            .Times(3)
            .WillOnce(Return(expected_first_task_id))
            .WillOnce(Return(expected_second_task_id))
            .WillOnce(Return(expected_third_task_id));

    TaskManager task_manager(std::move(gen));

    TaskId main_task_id = task_manager.AddTask(expected_first_task).second;
    TaskId subtask1_id = task_manager.AddSubTask(expected_second_task, main_task_id).second;
    TaskId subtask2_id = task_manager.AddSubTask(expected_third_task, main_task_id).second;

    const TaskActionResult expected_result = TaskActionResult::SUCCESS;
    const size_t expected_tasks_size = 3;
    // Act
    const TaskActionResult actual_result = task_manager.CompleteTask(main_task_id, true);
    const auto actual_tasks = task_manager.GetTasks();
    // Assert
    ASSERT_EQ(expected_result, actual_result);
    ASSERT_EQ(expected_tasks_size, actual_tasks.size());
    EXPECT_EQ(true, actual_tasks[0].task().completed());
    EXPECT_EQ(true, actual_tasks[1].task().completed());
    EXPECT_EQ(true, actual_tasks[2].task().completed());
}

TEST_F(TaskManagerTest, LoadState_ShouldLoadAllTasks) {
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    std::unique_ptr<MockTaskValidator> task_validator = std::make_unique<MockTaskValidator>();
    TaskId expected_last_id;
    expected_last_id.set_id(expected_third_task_id.id());
    EXPECT_CALL(*gen, CreateNewTaskId()).Times(0);
    EXPECT_CALL(*gen, SetLastTaskId(TaskId(expected_last_id))).Times(1);

    {
        testing::InSequence s;
        EXPECT_CALL(*task_validator, ValidateTask(expected_first_task)).WillOnce(Return(true));
        EXPECT_CALL(*task_validator, ValidateTask(expected_second_task)).WillOnce(Return(true));
        EXPECT_CALL(*task_validator, ValidateTask(expected_third_task)).WillOnce(Return(true));
    }
    TaskManager task_manager { std::move(gen), std::move(task_validator) };
    const auto expected_tasks = FormTasksToVector();
    const bool expected_result = true;
    // Act
    const bool actual_result = task_manager.LoadModelState(expected_tasks);
    const std::vector<RelationalTask> actual_tasks = task_manager.GetTasks();
    // Assert
    ASSERT_EQ(expected_result, actual_result);
    EXPECT_EQ(expected_tasks, actual_tasks);
}

TEST_F(TaskManagerTest, LoadState_TryLoadInvalidTasks_ShouldReturnFalse) {
    // Arrange
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    std::unique_ptr<MockTaskValidator> task_validator = std::make_unique<MockTaskValidator>();
    EXPECT_CALL(*gen, CreateNewTaskId()).Times(0);
    {
        testing::InSequence s;
        EXPECT_CALL(*task_validator, ValidateTask(expected_first_task)).WillOnce(Return(true));
        EXPECT_CALL(*task_validator, ValidateTask(expected_second_task)).WillOnce(Return(true));
        EXPECT_CALL(*task_validator, ValidateTask(expected_third_task)).WillOnce(Return(false));
    }
    TaskManager task_manager { std::move(gen), std::move(task_validator) };
    const auto tasks_to_load = FormTasksToVector();
    const bool expected_result = false;
    // Act
    const bool actual_result = task_manager.LoadModelState(tasks_to_load);
    // Assert
    EXPECT_EQ(expected_result, actual_result);
}

TEST_F(TaskManagerTest, GetTasksByLabel_ShouldReturnTasksWithCertainLabel) {
    // Arrange
    const std::string expected_search_label = "label";
    expected_first_task.add_label(expected_search_label);
    expected_third_task.add_label(expected_search_label);
    std::unique_ptr<MockIdGenerator> gen(new MockIdGenerator);
    EXPECT_CALL(*gen, CreateNewTaskId())
            .Times(3)
            .WillOnce(Return(expected_first_task_id))
            .WillOnce(Return(expected_second_task_id))
            .WillOnce(Return(expected_third_task_id));
    TaskManager task_manager { std::move(gen) };

    TaskId main_task_id = task_manager.AddTask(expected_first_task).second;
    TaskId subtask1_id = task_manager.AddSubTask(expected_second_task, main_task_id).second;
    TaskId subtask2_id = task_manager.AddSubTask(expected_third_task, main_task_id).second;

    RelationalTask tt1;
    tt1.set_allocated_task(new Task(expected_first_task));
    tt1.set_allocated_task_id(new TaskId(expected_first_task_id));
    RelationalTask tt3;
    tt3.set_allocated_task(new Task(expected_third_task));
    tt3.set_allocated_task_id(new TaskId(expected_third_task_id));
    tt3.set_allocated_parent_id(new TaskId(expected_first_task_id));

    const std::vector<RelationalTask> expected_returned_tasks { tt1, tt3 };
    // Act
    const std::vector<RelationalTask> actual_returned_tasks = task_manager.GetTasksByLabel(expected_search_label);
    // Assert
    ASSERT_EQ(expected_returned_tasks.size(), actual_returned_tasks.size());
    EXPECT_EQ(expected_returned_tasks, actual_returned_tasks);
}