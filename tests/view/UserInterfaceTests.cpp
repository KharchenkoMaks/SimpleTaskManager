//
// Created by Maksym Kharchenko on 12.01.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "view/user_interface/UserInterface.h"

#include "view/states/RootState.h"
#include "view/states/ShowState.h"
#include "view/commands/AddTaskCommand.h"

#include "mocks/MockStatesFactory.h"
#include "mocks/MockCommandFactory.h"
#include "mocks/MockConsolePrinter.h"
#include "mocks/MockConsoleReader.h"
#include "mocks/MockStateMachine.h"

#include "utilities/TaskComparators.h"

#include <google/protobuf/util/time_util.h>

using ::testing::Return;

class UserInterfaceTests : public ::testing::Test {
public:
    std::shared_ptr<MockStatesFactory> states_factory_;
    std::shared_ptr<MockConsolePrinter> console_printer_;
    std::shared_ptr<MockConsoleReader> console_reader_;
    std::shared_ptr<MockCommandFactory> command_factory_;
    void SetUp() override {
        states_factory_ = std::make_shared<MockStatesFactory>();
        console_printer_ = std::make_shared<MockConsolePrinter>();
        console_reader_ = std::make_shared<MockConsoleReader>();
        command_factory_ = std::make_shared<MockCommandFactory>();
        EXPECT_CALL(*states_factory_, GetConsolePrinter()).WillRepeatedly(Return(console_printer_));
        EXPECT_CALL(*states_factory_, GetConsoleReader()).WillRepeatedly(Return(console_reader_));
        EXPECT_CALL(*states_factory_, GetCommandFactory()).WillRepeatedly(Return(command_factory_));
    }
};

bool operator==(const std::shared_ptr<StateContext>& context1, const std::shared_ptr<StateContext>& context2) {
    return context1->GetTasksToShow() == context2->GetTasksToShow();
}

TEST_F(UserInterfaceTests, AskUserForAction_ShouldRunStateMachineAndReturnCommandFromContext) {
    // Arrange
    UserInterface ui { states_factory_ };
    std::unique_ptr<MockStateMachine> state_machine = std::make_unique<MockStateMachine>();
    std::shared_ptr<StateInterface> expected_root_state = std::make_shared<RootState>(nullptr);
    std::shared_ptr<StateContext> returned_context = std::make_shared<StateContext>();
    std::unique_ptr<AddTaskCommand> expected_command = std::make_unique<AddTaskCommand>(Task::default_instance());
    std::reference_wrapper<AddTaskCommand> expected_returned_command(*expected_command);
    returned_context->SetCommand(std::move(expected_command));
    // Assert
    EXPECT_CALL(*state_machine, Run(testing::_, expected_root_state)).WillOnce(Return(returned_context));
    EXPECT_CALL(*states_factory_, CreateStateMachine()).WillOnce(Return(testing::ByMove(std::move(state_machine))));
    EXPECT_CALL(*states_factory_, GetRootState()).WillOnce(Return(expected_root_state));
    // Act
    std::shared_ptr<CommandInterface> actual_returned_command = ui.AskUserForAction();
    // Assert
    EXPECT_EQ(&expected_returned_command.get(), actual_returned_command.get());
}

TEST_F(UserInterfaceTests, PrintAddedTaskId_ShouldPrintGivenTaskId) {
    // Arrange
    UserInterface ui { states_factory_ };
    TaskId task_id;
    task_id.set_id(42);
    // Assert
    EXPECT_CALL(*console_printer_, WriteLine("Task was successfully added, TaskId: " + std::to_string(task_id.id())));
    // Act
    ui.PrintAddedTaskId(task_id);
}

TEST_F(UserInterfaceTests, ShowTasks_ShouldStartStateMachineToShowTasks) {
    // Arrange
    UserInterface ui { states_factory_ };
    std::unique_ptr<MockStateMachine> state_machine = std::make_unique<MockStateMachine>();
    std::shared_ptr<StateInterface> expected_show_state = std::make_shared<ShowState>(nullptr);
    std::shared_ptr<StateContext> expected_show_state_context = std::make_shared<StateContext>();

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

    std::vector<TaskTransfer> tasks_to_show { tt1, tt3, tt2 };

    expected_show_state_context->SetTasksToShow(tasks_to_show);
    // Assert
    EXPECT_CALL(*state_machine, Run(expected_show_state_context, expected_show_state)).Times(1);
    EXPECT_CALL(*states_factory_, CreateStateMachine()).WillOnce(Return(testing::ByMove(std::move(state_machine))));
    EXPECT_CALL(*states_factory_, GetShowState()).WillOnce(Return(expected_show_state));
    // Act
    ui.ShowTasks(tasks_to_show);
}

TEST_F(UserInterfaceTests, PrintRequestResult_ShouldPrintRightString) {
    // Arrange
    UserInterface ui { states_factory_ };
    std::vector<std::pair<ControllerRequestResult, std::string>> expected_prints = {
            std::pair(ControllerRequestResult::FAIL_INVALID_TASK, "Invalid task was given."),
            std::pair(ControllerRequestResult::FAIL_UNCOMPLETED_SUBTASKS, "Found uncompleted subtasks of this task."),
            std::pair(ControllerRequestResult::FAIL_NOT_DELETED_SUBTASKS, "Found not deleted subtask of this task."),
            std::pair(ControllerRequestResult::FAIL_NO_SUCH_TASK, "No task with such id was found."),
            std::pair(ControllerRequestResult::FILE_WAS_NOT_OPENED, "Couldn't open the file."),
            std::pair(ControllerRequestResult::FILE_DAMAGED, "File is damaged."),
    };
    // Act & Assert
    EXPECT_CALL(*console_printer_, WriteLine("Action success.")).Times(1);
    ui.PrintRequestResult(ControllerRequestResult::SUCCESS);
    for (const auto expected_print : expected_prints) {
        EXPECT_CALL(*console_printer_, WriteError(expected_print.second)).Times(1);
        ui.PrintRequestResult(expected_print.first);
    }
}