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
#include "view/states/task_input/AddLabelState.h"
#include "view/states/CompleteTaskState.h"
#include "view/states/DeleteTaskState.h"
#include "view/states/HelpState.h"
#include "view/states/InputShowParametersState.h"
#include "view/states/InputShowByLabelState.h"
#include "view/states/QuitState.h"
#include "view/states/RootState.h"
#include "view/states/ShowState.h"
#include "view/states/persistence/LoadState.h"
#include "view/states/persistence/SaveState.h"
#include "view/states/task_input/RemoveLabelState.h"

#include "mocks/MockStatesFactory.h"
#include "mocks/MockCommandFactory.h"
#include "mocks/MockConsolePrinter.h"
#include "mocks/MockConsoleReader.h"
#include "mocks/MockStateMachine.h"

#include "utilities/TaskConvertors.h"
#include "utilities/TaskComparators.h"

#include <utility>
#include <ctime>
#include <google/protobuf/util/time_util.h>

using ::testing::Return;
using ::testing::ByMove;

class StatesTests : public ::testing::Test {
public:
    StateType expected_state_machine_initial_state;
    StateType expected_error_state;
    StateType expected_next_state;

    std::unique_ptr<MockStateMachine> state_machine;

    std::shared_ptr<MockConsolePrinter> console_printer_;
    std::shared_ptr<MockConsoleReader> console_reader_;
    std::shared_ptr<MockCommandFactory> command_factory_;

    testing::Sequence user_input_sequence_;
    void SetUp() override {
        expected_state_machine_initial_state = StateType::kInputTaskTitle;
        expected_next_state = StateType::kEnd;
        expected_error_state = StateType::kRoot;

        state_machine = std::make_unique<MockStateMachine>();

        console_printer_ = std::make_shared<MockConsolePrinter>();
        console_reader_ = std::make_shared<MockConsoleReader>();
        command_factory_ = std::make_shared<MockCommandFactory>();
    }
    void ExpectGetUserInput(const std::string& message, const std::string& returned_input) {
        EXPECT_CALL(*console_printer_, Write(message + "> ")).InSequence(user_input_sequence_);
        EXPECT_CALL(*console_reader_, ReadLine()).InSequence(user_input_sequence_).WillOnce(Return(returned_input));
    }
    std::unique_ptr<StateContext> GetContextWithFilledTask() {
        auto context_with_task = std::make_unique<StateContext>();
        context_with_task->AddTaskTitle("Task title");
        context_with_task->AddTaskPriority(Task::Priority::Task_Priority_LOW);
        context_with_task->AddTaskDueTime(google::protobuf::Timestamp(google::protobuf::util::TimeUtil::TimeTToTimestamp(time(0))));
        context_with_task->SetTaskLabel("Task label");
        return std::move(context_with_task);
    }
};

TEST_F(StatesTests, AddSubTaskStateExecuteShouldCreateAddSubTaskCommand) {
    // Arrange
    std::unique_ptr<StateContext> expected_returned_context_from_state_machine = GetContextWithFilledTask();
    Task expected_task_from_state_machine = expected_returned_context_from_state_machine->GetTaskBuilder().BuildTask();
    StateContext add_subtask_context;
    const std::string expected_parent_id_input = "5";
    const int expected_task_id = std::stoi(expected_parent_id_input);

    ExpectGetUserInput("Parent Task ID", expected_parent_id_input);

    EXPECT_CALL(*state_machine, Run())
            .WillOnce(Return(ByMove(std::move(expected_returned_context_from_state_machine))));

    EXPECT_CALL(*command_factory_, CreateAddSubTaskCommand(testing::Ref(add_subtask_context))).Times(1);

    AddSubTaskState add_subtask_state(expected_next_state, expected_error_state, console_printer_, console_reader_, command_factory_, std::move(state_machine));
    // Act
    const StateType actual_next_state = add_subtask_state.Execute(add_subtask_context);
    // Assert
    ASSERT_TRUE(add_subtask_context.GetTaskId().has_value());
    EXPECT_EQ(expected_task_id, add_subtask_context.GetTaskId().value().id());
    EXPECT_EQ(add_subtask_context.GetTaskBuilder().BuildTask(), expected_task_from_state_machine);
    EXPECT_EQ(expected_next_state, actual_next_state);
}

TEST_F(StatesTests, AddSubTaskStateExecuteGivenWrongParentId_ShouldReturnErrorNextState) {
    // Assert
    StateContext add_subtask_context;
    EXPECT_CALL(*state_machine, Run()).Times(0);
    AddSubTaskState add_subtask_state(expected_next_state, expected_error_state, console_printer_, console_reader_, command_factory_, std::move(state_machine));
    // Assert
    ExpectGetUserInput("Parent Task ID", "qwe");

    EXPECT_CALL(*console_printer_, WriteError("Incorrect task id was given, try again!")).Times(1);
    // Act
    const StateType actual_next_state = add_subtask_state.Execute(add_subtask_context);
    // Assert
    EXPECT_EQ(expected_error_state, actual_next_state);
}

TEST_F(StatesTests, AddTaskExecuteShouldCreateAddTaskCommand) {
    std::unique_ptr<StateContext> expected_returned_context_from_state_machine = GetContextWithFilledTask();
    Task expected_task_from_state_machine = expected_returned_context_from_state_machine->GetTaskBuilder().BuildTask();
    StateContext add_task_context;
    // Assert
    EXPECT_CALL(*state_machine, Run())
            .WillOnce(Return(ByMove(std::move(expected_returned_context_from_state_machine))));

    EXPECT_CALL(*command_factory_, CreateAddTaskCommand(testing::Ref(add_task_context))).Times(1);

    AddTaskState add_task_state(expected_next_state, command_factory_, std::move(state_machine));
    // Act
    const StateType actual_next_state = add_task_state.Execute(add_task_context);
    // Assert
    EXPECT_EQ(add_task_context.GetTaskBuilder().BuildTask(), expected_task_from_state_machine);
    EXPECT_EQ(expected_next_state, actual_next_state);
}

TEST_F(StatesTests, EditTaskExecuteShouldCreateEditTaskCommand) {
    // Arrange
    std::unique_ptr<StateContext> expected_returned_context_from_state_machine = GetContextWithFilledTask();
    Task expected_task_from_state_machine = expected_returned_context_from_state_machine->GetTaskBuilder().BuildTask();
    StateContext edit_task_context;

    const std::string expected_input_id = "5";

    // Assert
    ExpectGetUserInput("Task ID", expected_input_id);

    EXPECT_CALL(*state_machine, Run())
            .WillOnce(Return(ByMove(std::move(expected_returned_context_from_state_machine))));

    EXPECT_CALL(*command_factory_, CreateEditCommand(testing::Ref(edit_task_context))).Times(1);

    EditTaskState edit_task_state(expected_next_state, expected_error_state, console_printer_, console_reader_, command_factory_, std::move(state_machine));
    // Act
    const StateType actual_next_state = edit_task_state.Execute(edit_task_context);
    // Assert
    EXPECT_EQ(edit_task_context.GetTaskBuilder().BuildTask(), expected_task_from_state_machine);
    EXPECT_EQ(std::stoi(expected_input_id), edit_task_context.GetTaskId().value().id());
    EXPECT_EQ(expected_next_state, actual_next_state);
}

TEST_F(StatesTests, EditTaskStateExecuteGivenWrongTaskId_ShouldReturnErrorNextState) {
    // Arrange
    StateContext edit_task_context;
    // Assert
    ExpectGetUserInput("Task ID", "qwe");

    EXPECT_CALL(*console_printer_, WriteError("Incorrect task id was given, try again!")).Times(1);
    EXPECT_CALL(*state_machine, Run()).Times(0);

    EditTaskState edit_task_state(expected_next_state, expected_error_state, console_printer_, console_reader_, command_factory_, std::move(state_machine));
    // Act
    const StateType actual_next_state = edit_task_state.Execute(edit_task_context);
    // Assert
    EXPECT_EQ(expected_error_state, actual_next_state);
}

// Inputting due date with time
TEST_F(StatesTests, InputTaskDueDateStateExecute_ShouldAddTimeToContext) {
    // Arrange
    StateContext input_due_date_context;
    InputTaskDueDateState input_due_date_state(expected_next_state, expected_error_state, console_printer_, console_reader_);

    const std::string expected_input_due_date = "16:30 01.01.2030";
    const google::protobuf::Timestamp expected_timestamp = StringToTime(expected_input_due_date).value();
    // Assert
    ExpectGetUserInput("Due Date, format: 12:00 01.01.2000", expected_input_due_date);
    // Act
    const StateType actual_next_state = input_due_date_state.Execute(input_due_date_context);
    // Assert
    EXPECT_EQ(expected_next_state, actual_next_state);
    EXPECT_EQ(expected_timestamp, input_due_date_context.GetTaskBuilder().BuildTask().due_date());
}

// Inputting due date without time
TEST_F(StatesTests, InputTaskDueDateStateExecuteGivingDueDateWithoutTime_ShouldAddTimeToContext) {
    // Arrange
    StateContext input_due_date_context;
    InputTaskDueDateState input_due_date_state(expected_next_state, expected_error_state, console_printer_, console_reader_);

    const std::string expected_input_due_date = "01.01.2030";
    const google::protobuf::Timestamp expected_timestamp = StringToTime(expected_input_due_date, "%d.%m.%Y").value();
    // Assert
    ExpectGetUserInput("Due Date, format: 12:00 01.01.2000", expected_input_due_date);
    // Act
    const StateType actual_next_state = input_due_date_state.Execute(input_due_date_context);
    // Assert
    EXPECT_EQ(expected_next_state, actual_next_state);
    EXPECT_EQ(expected_timestamp, input_due_date_context.GetTaskBuilder().BuildTask().due_date());
}

// Inputting incorrect due date
TEST_F(StatesTests, InputTaskDueDateStateExecuteGivingIncorrectDueDate_ShouldPrintError) {
    // Arrange
    StateContext input_due_date_context;
    InputTaskDueDateState input_due_date_state(expected_next_state, expected_error_state, console_printer_, console_reader_);

    const std::string expected_input_due_date = "some text, not due date";
    // Assert
    ExpectGetUserInput("Due Date, format: 12:00 01.01.2000", expected_input_due_date);
    EXPECT_CALL(*console_printer_, WriteError("Wrong due date was given, try again!")).Times(1);
    // Act
    const StateType actual_next_state = input_due_date_state.Execute(input_due_date_context);
    // Assert
    EXPECT_EQ(expected_error_state, actual_next_state);
}

// Inputting due date from past
TEST_F(StatesTests, InputTaskDueDateStateExecuteGivingDueDateFromPast_ShouldPrintError) {
    // Arrange
    StateContext input_due_date_context;
    InputTaskDueDateState input_due_date_state(expected_next_state, expected_error_state, console_printer_, console_reader_);

    const std::string expected_input_due_date = "01.01.2011";
    // Assert
    ExpectGetUserInput("Due Date, format: 12:00 01.01.2000", expected_input_due_date);
    EXPECT_CALL(*console_printer_, WriteError("Due time should be in future, try again!")).Times(1);
    // Act
    const StateType actual_next_state = input_due_date_state.Execute(input_due_date_context);
    // Assert
    EXPECT_EQ(expected_error_state, actual_next_state);
}

TEST_F(StatesTests, InputTaskPriorityStateExecute_ShouldPutPriorityInContext) {
    // Arrange
    StateContext input_priority_context;
    InputTaskPriorityState input_priority_state(expected_next_state, expected_error_state, console_printer_, console_reader_);

    const std::string expected_input_priority = "Low";
    const Task::Priority expected_priority = StringToTaskPriority(expected_input_priority).value();
    // Assert
    ExpectGetUserInput("Priority (High, Medium, Low, None)", expected_input_priority);
    // Act
    const StateType actual_next_state = input_priority_state.Execute(input_priority_context);
    // Assert
    EXPECT_EQ(expected_next_state, actual_next_state);
    EXPECT_EQ(expected_priority, input_priority_context.GetTaskBuilder().BuildTask().priority());
}

TEST_F(StatesTests, InputTaskPriorityStateExecuteGivingIncorrectPriority_ShouldPrintError) {
    // Arrange
    StateContext input_priority_context;
    InputTaskPriorityState input_priority_state(expected_next_state, expected_error_state, console_printer_, console_reader_);

    const std::string expected_input_priority = "some text, not priority";
    // Assert
    ExpectGetUserInput("Priority (High, Medium, Low, None)", expected_input_priority);
    EXPECT_CALL(*console_printer_, WriteError("Wrong task priority was given, try [High, Medium, Low, None]!")).Times(1);
    // Act
    const StateType actual_next_state = input_priority_state.Execute(input_priority_context);
    // Assert
    EXPECT_EQ(expected_error_state, actual_next_state);
}

TEST_F(StatesTests, InputTaskTitleStateExecute_ShouldPutTitleInContext) {
    // Arrange
    StateContext input_title_context;
    InputTaskTitleState input_title_state(expected_next_state, console_printer_, console_reader_);

    const std::string expected_input_title = "Some Task Title";
    // Assert
    ExpectGetUserInput("Title", expected_input_title);
    // Act
    const StateType actual_next_state = input_title_state.Execute(input_title_context);
    // Assert
    EXPECT_EQ(expected_next_state, actual_next_state);
    EXPECT_EQ(expected_input_title, input_title_context.GetTaskBuilder().BuildTask().title());
}

TEST_F(StatesTests, AddLabelStateExecute_ShouldCreateSetLabelCommand) {
    // Arrange
    StateContext set_label_context;
    AddLabelState add_label_state(expected_next_state, expected_error_state, console_printer_, console_reader_, command_factory_);

    const std::string expected_input_label = "Some Task Label";
    const std::string expected_input_id = "5";
    // Assert
    {
        testing::InSequence s;
        EXPECT_CALL(*console_printer_, Write("Task ID> ")).Times(1);
        EXPECT_CALL(*console_printer_, Write("Label> ")).Times(1);
    }
    EXPECT_CALL(*console_reader_, ReadLine())
        .WillOnce(Return(expected_input_id))
        .WillOnce(Return(expected_input_label));
    EXPECT_CALL(*command_factory_, CreateSetLabelCommand(testing::Ref(set_label_context))).Times(1);
    // Act
    const StateType actual_next_state = add_label_state.Execute(set_label_context);
    // Assert
    EXPECT_EQ(std::stoi(expected_input_id), set_label_context.GetTaskId().value().id());
    EXPECT_EQ(expected_input_label, set_label_context.GetTaskLabel());
    EXPECT_EQ(expected_next_state, actual_next_state);
}

TEST_F(StatesTests, AddLabelStateExecuteGivingWrongTaskId_ShouldPrintError) {
    // Arrange
    StateContext set_label_context;
    AddLabelState add_label_state(expected_next_state, expected_error_state, console_printer_, console_reader_, command_factory_);

    const std::string expected_input_id = "some text, not task id";
    // Assert
    ExpectGetUserInput("Task ID", expected_input_id);
    EXPECT_CALL(*console_printer_, WriteError("Incorrect task id was given, try again!")).Times(1);
    // Act
    const StateType actual_next_state = add_label_state.Execute(set_label_context);
    // Assert
    EXPECT_EQ(expected_error_state, actual_next_state);
}

TEST_F(StatesTests, RemoveLabelStateExecute_ShouldCreateRemoveLabelCommand) {
    // Arrange
    StateContext remove_label_context;
    RemoveLabelState remove_label_state(expected_next_state, expected_error_state, console_printer_, console_reader_, command_factory_);

    const std::string expected_input_label = "Some Task Label";
    const std::string expected_input_id = "5";
    // Assert
    {
        testing::InSequence s;
        EXPECT_CALL(*console_printer_, Write("Task ID> ")).Times(1);
        EXPECT_CALL(*console_printer_, Write("Label> ")).Times(1);
    }
    EXPECT_CALL(*console_reader_, ReadLine())
            .WillOnce(Return(expected_input_id))
            .WillOnce(Return(expected_input_label));
    EXPECT_CALL(*command_factory_, CreateRemoveLabelCommand(testing::Ref(remove_label_context))).Times(1);
    // Act
    const StateType actual_next_state = remove_label_state.Execute(remove_label_context);
    // Assert
    EXPECT_EQ(std::stoi(expected_input_id), remove_label_context.GetTaskId().value().id());
    EXPECT_EQ(expected_input_label, remove_label_context.GetTaskLabel());
    EXPECT_EQ(expected_next_state, actual_next_state);
}

TEST_F(StatesTests, RemoveLabelStateExecuteGivingWrongTaskId_ShouldPrintError) {
    // Arrange
    StateContext remove_label_context;
    RemoveLabelState remove_label_state(expected_next_state, expected_error_state, console_printer_, console_reader_, command_factory_);

    const std::string expected_input_id = "some text, not task id";
    // Assert
    ExpectGetUserInput("Task ID", expected_input_id);
    EXPECT_CALL(*console_printer_, WriteError("Incorrect task id was given, try again!")).Times(1);
    // Act
    const StateType actual_next_state = remove_label_state.Execute(remove_label_context);
    // Assert
    EXPECT_EQ(expected_error_state, actual_next_state);
}

TEST_F(StatesTests, CompleteTaskStateExecute_ShouldCreateCompleteTaskCommand) {
    // Arrange
    StateContext complete_task_context;
    CompleteTaskState complete_task_state(expected_next_state, expected_error_state, console_printer_, console_reader_, command_factory_);

    const std::string expected_input_string_id = "5";
    const TaskId expected_input_id = StringToTaskId(expected_input_string_id).value();
    const std::string expected_confirm_input = "y";
    const bool expected_confirmation = true;
    // Assert
    ExpectGetUserInput("Task ID", expected_input_string_id);
    ExpectGetUserInput("Complete all subtasks? y/n", expected_confirm_input);
    EXPECT_CALL(*command_factory_, CreateCompleteCommand(testing::Ref(complete_task_context), expected_confirmation)).Times(1);
    // Act
    const StateType actual_next_state = complete_task_state.Execute(complete_task_context);
    // Assert
    EXPECT_EQ(std::stoi(expected_input_string_id), complete_task_context.GetTaskId().value().id());
    EXPECT_EQ(expected_next_state, actual_next_state);
}

TEST_F(StatesTests, CompleteTaskStateExecuteWithIncorrectTaskId_ShouldPrintError) {
    // Arrange
    StateContext complete_task_context;
    CompleteTaskState complete_task_state(expected_next_state, expected_error_state, console_printer_, console_reader_, command_factory_);

    const std::string expected_input_string_id = "some text, not task id";
    // Assert
    ExpectGetUserInput("Task ID", expected_input_string_id);
    EXPECT_CALL(*console_printer_, WriteError("Incorrect task id was given, try again!")).Times(1);
    // Act
    const StateType actual_next_state = complete_task_state.Execute(complete_task_context);
    // Assert
    EXPECT_EQ(expected_error_state, actual_next_state);
}

TEST_F(StatesTests, DeleteTaskStateExecute_ShouldCreateDeleteTaskCommand) {
    // Arrange
    StateContext delete_task_context;
    DeleteTaskState delete_task_state(expected_next_state, expected_error_state, console_printer_, console_reader_, command_factory_);

    const std::string expected_input_string_id = "7";
    const TaskId expected_input_id = StringToTaskId(expected_input_string_id).value();
    const std::string expected_confirm_input = "n";
    const bool expected_confirmation = false;
    // Assert
    ExpectGetUserInput("Task ID", expected_input_string_id);
    ExpectGetUserInput("Delete all subtasks? y/n", expected_confirm_input);
    EXPECT_CALL(*command_factory_, CreateDeleteCommand(testing::Ref(delete_task_context), expected_confirmation)).Times(1);
    // Act
    const StateType actual_next_state = delete_task_state.Execute(delete_task_context);
    // Assert
    EXPECT_EQ(std::stoi(expected_input_string_id), delete_task_context.GetTaskId().value().id());
    EXPECT_EQ(expected_next_state, actual_next_state);
}

TEST_F(StatesTests, DeleteTaskStateExecuteWithIncorrectTaskId_ShouldPrintError) {
    // Arrange
    StateContext delete_task_context;
    DeleteTaskState delete_task_state(expected_next_state, expected_error_state, console_printer_, console_reader_, command_factory_);

    const std::string expected_input_string_id = "some text, not task id";
    // Assert
    ExpectGetUserInput("Task ID", expected_input_string_id);
    EXPECT_CALL(*console_printer_, WriteError("Incorrect task id was given, try again!")).Times(1);
    // Act
    const StateType actual_next_state = delete_task_state.Execute(delete_task_context);
    // Assert
    EXPECT_EQ(expected_error_state, actual_next_state);
}

TEST_F(StatesTests, HelpStateExecute_ShouldPrintHelpMessage) {
    // Arrange
    StateContext help_state_context;
    HelpState help_state(expected_next_state, console_printer_);
    // Assert
    {
        testing::InSequence s;
        EXPECT_CALL(*console_printer_, WriteLine("Available commands:"));
        EXPECT_CALL(*console_printer_, WriteLine("1. add"));
        EXPECT_CALL(*console_printer_, WriteLine("2. add_subtask"));
        EXPECT_CALL(*console_printer_, WriteLine("3. edit"));
        EXPECT_CALL(*console_printer_, WriteLine("4. delete"));
        EXPECT_CALL(*console_printer_, WriteLine("5. complete"));
        EXPECT_CALL(*console_printer_, WriteLine("6. add_label"));
        EXPECT_CALL(*console_printer_, WriteLine("7. remove_label"));
        EXPECT_CALL(*console_printer_, WriteLine("8. show"));
        EXPECT_CALL(*console_printer_, WriteLine("9. save"));
        EXPECT_CALL(*console_printer_, WriteLine("10. load"));
        EXPECT_CALL(*console_printer_, WriteLine("11. quit"));
    }
    // Act
    const StateType actual_next_state = help_state.Execute(help_state_context);
    // Assert
    EXPECT_EQ(expected_next_state, actual_next_state);
}

TEST_F(StatesTests, InputShowParametersStateExecute_ShouldCreateShowCommand) {
    // Arrange
    StateContext show_state_context;
    // Assert
    EXPECT_CALL(*command_factory_, CreateShowCommand(testing::Ref(show_state_context))).Times(1);
    EXPECT_CALL(*state_machine, Run()).WillOnce(Return(ByMove(std::make_unique<StateContext>())));

    InputShowParametersState input_show_state(expected_next_state, command_factory_, std::move(state_machine));
    // Act
    const StateType actual_next_state = input_show_state.Execute(show_state_context);
    // Assert
    EXPECT_EQ(expected_next_state, actual_next_state);
    EXPECT_EQ("", show_state_context.GetTaskLabel());
}

TEST_F(StatesTests, InputSortByLabelStateExecute_ShouldAskUserForTaskLabelToShow) {
    // Arrange
    StateContext input_show_label_state_context;
    InputShowByLabelState input_show_label_state(expected_next_state, console_printer_, console_reader_);

    const std::string expected_label_input = "some label";
    // Assert
    EXPECT_CALL(*console_printer_, Write("Label to sort by> ")).Times(1);
    EXPECT_CALL(*console_reader_, ReadLine()).WillOnce(Return(expected_label_input));
    // Act
    const StateType actual_next_state = input_show_label_state.Execute(input_show_label_state_context);
    // Assert
    EXPECT_EQ(expected_label_input, input_show_label_state_context.GetTaskLabel());
    EXPECT_EQ(expected_next_state, actual_next_state);
}

TEST_F(StatesTests, QuitStateExecuteConfirm_ShouldReturnNextState) {
    // Arrange
    StateContext quit_state_context;
    QuitState quit_state(expected_next_state, expected_error_state, console_printer_, console_reader_);
    const std::string expected_confirm_string = "y";
    // Assert
    ExpectGetUserInput("Are you sure? y/n", expected_confirm_string);
    // Act
    const StateType actual_next_state = quit_state.Execute(quit_state_context);
    // Assert
    EXPECT_EQ(expected_next_state, actual_next_state);
}

TEST_F(StatesTests, QuitStateExecuteNotConfirm_ShouldReturnErrorState) {
    // Arrange
    StateContext quit_state_context;
    QuitState quit_state(expected_next_state, expected_error_state, console_printer_, console_reader_);
    const std::string expected_confirm_string = "no";
    // Assert
    ExpectGetUserInput("Are you sure? y/n", expected_confirm_string);
    // Act
    const StateType actual_next_state = quit_state.Execute(quit_state_context);
    // Assert
    EXPECT_EQ(expected_error_state, actual_next_state);
}

TEST_F(StatesTests, RootStateExecuteWithRightCommand_ShouldReturnNextState) {
    // Arrange
    StateContext root_state_context;
    RootState root_state(expected_error_state, console_printer_, console_reader_);

    const std::vector<std::pair<std::string, StateType>> expected_commands {
        std::pair("add", StateType::kAddTask),
        std::pair("add_subtask", StateType::kAddSubTask),
        std::pair("edit", StateType::kEditTask),
        std::pair("delete", StateType::kDelete),
        std::pair("complete", StateType::kComplete),
        std::pair("show", StateType::kInputShowParameters),
        std::pair("help", StateType::kHelp),
        std::pair("quit", StateType::kQuit),
        std::pair("add_label", StateType::kAddLabel),
        std::pair("remove_label", StateType::kRemoveLabel),
        std::pair("save", StateType::kSave),
        std::pair("load", StateType::kLoad),
    };
    // Act & Assert
    for (const auto& case_ : expected_commands) {
        ExpectGetUserInput("", case_.first);

        const StateType actual_next_state = root_state.Execute(root_state_context);

        EXPECT_EQ(case_.second, actual_next_state);
    }
}

TEST_F(StatesTests, RootStateExecuteWithIncorrectCommand_ShouldPrintError) {
    // Arrange
    StateContext root_state_context;
    RootState root_state(expected_error_state, console_printer_, console_reader_);

    const std::string expected_input_command = "not command";
    // Assert
    ExpectGetUserInput("", expected_input_command);
    EXPECT_CALL(*console_printer_, WriteError("Unknown command! Use help.")).Times(1);
    // Act
    const StateType actual_next_state = root_state.Execute(root_state_context);
    // Assert
    EXPECT_EQ(expected_error_state, actual_next_state);
}

TEST_F(StatesTests, ShowStateExecute_ShouldPrintAllTasksFromContext) {
    // Arrange
    StateContext show_state_context;
    ShowState show_state(expected_next_state, console_printer_);

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

    std::vector<RelationalTask> tasks_to_show {tt1, tt3, tt2 };

    show_state_context.SetTasksToShow(tasks_to_show);

    // Assert
    {
        testing::InSequence s;
        EXPECT_CALL(*console_printer_, WriteLine(TaskToString(parent_task_id, t1))).Times(1);
        EXPECT_CALL(*console_printer_, WriteLine("\t" + TaskToString(task3_id, t3))).Times(1);
        EXPECT_CALL(*console_printer_, WriteLine(TaskToString(task2_id, t2))).Times(1);
    }
    // Act
    const StateType actual_next_state = show_state.Execute(show_state_context);
    // Assert
    EXPECT_EQ(expected_next_state, actual_next_state);
}

TEST_F(StatesTests, LoadStateExecute_ShouldCreateLoadCommand) {
    // Arrange
    StateContext load_state_context;
    LoadState load_state(expected_next_state, expected_error_state, console_printer_, console_reader_, command_factory_);

    const std::string expected_input_file_name = "some_file.txt";
    // Assert
    ExpectGetUserInput("File name", expected_input_file_name);
    EXPECT_CALL(*command_factory_, CreateLoadCommand(testing::Ref(load_state_context))).Times(1);
    // Act
    const StateType actual_next_state = load_state.Execute(load_state_context);
    // Assert
    EXPECT_EQ(expected_next_state, actual_next_state);
    EXPECT_EQ(expected_input_file_name, load_state_context.GetFileName());
}

TEST_F(StatesTests, LoadStateExecute_ShouldPrintErrorOnEmpyFileName) {
    // Arrange
    StateContext load_state_context;
    LoadState load_state(expected_next_state, expected_error_state, console_printer_, console_reader_, command_factory_);

    const std::string expected_input_file_name = "";
    // Assert
    ExpectGetUserInput("File name", expected_input_file_name);
    EXPECT_CALL(*command_factory_, CreateLoadCommand(testing::Ref(load_state_context))).Times(0);
    EXPECT_CALL(*console_printer_, WriteError("Invalid file name!")).Times(1);
    // Act
    const StateType actual_next_state = load_state.Execute(load_state_context);
    // Assert
    EXPECT_EQ(expected_error_state, actual_next_state);
}

TEST_F(StatesTests, SaveStateExecute_ShouldCreateSaveCommand) {
    // Arrange
    StateContext save_state_context;
    SaveState save_state(expected_next_state, expected_error_state, console_printer_, console_reader_, command_factory_);

    const std::string expected_input_file_name = "some_file.txt";
    // Assert
    ExpectGetUserInput("File name", expected_input_file_name);
    EXPECT_CALL(*command_factory_, CreateSaveCommand(testing::Ref(save_state_context))).Times(1);
    // Act
    const StateType actual_next_state = save_state.Execute(save_state_context);
    // Assert
    EXPECT_EQ(expected_next_state, actual_next_state);
    EXPECT_EQ(expected_input_file_name, save_state_context.GetFileName());
}

TEST_F(StatesTests, SaveStateExecute_ShouldPrintErrorOnEmpyFileName) {
    // Arrange
    StateContext save_state_context;
    SaveState save_state(expected_next_state, expected_error_state, console_printer_, console_reader_, command_factory_);

    const std::string expected_input_file_name = "";
    // Assert
    ExpectGetUserInput("File name", expected_input_file_name);
    EXPECT_CALL(*command_factory_, CreateSaveCommand(testing::Ref(save_state_context))).Times(0);
    EXPECT_CALL(*console_printer_, WriteError("Invalid file name!")).Times(1);
    // Act
    const StateType actual_next_state = save_state.Execute(save_state_context);
    // Assert
    EXPECT_EQ(expected_error_state, actual_next_state);
}
