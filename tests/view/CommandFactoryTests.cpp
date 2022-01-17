//
// Created by Maksym Kharchenko on 17.01.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "view/commands/factory/CommandFactory.h"

#include "commands/Command.h"

#include "commands/AddSubTaskCommand.h"
#include "commands/AddTaskCommand.h"
#include "commands/EditTaskCommand.h"
#include "commands/CompleteTaskCommand.h"
#include "commands/DeleteTaskCommand.h"
#include "commands/SetLabelCommand.h"
#include "commands/ShowTasksCommand.h"
#include "commands/SaveCommand.h"
#include "commands/LoadCommand.h"
#include "commands/RemoveLabelCommand.h"

#include "view/user_interface/StateContext.h"

#include "utilities/TaskBuilder.h"
#include "utilities/TaskConvertors.h"

#include <typeinfo>

class CommandFactoryTests : public ::testing::Test {
public:
    CommandFactory factory_;

    TaskBuilder task_builder_ = TaskBuilder::Create();
    TaskId task_id_;
    std::string file_name_;

    StateContext context_;

    void SetUp() override {
        task_builder_.SetTitle("task title")
            .SetPriority(Task::Priority::Task_Priority_MEDIUM)
            .SetDueDate(StringToTime("15:00 01.01.2030").value());

        task_id_.set_id(42);

        file_name_ = "some_file";
    }

    template<class TExpected>
    void TestCommandType(const Command& actual_command) {
        EXPECT_EQ(typeid(TExpected), typeid(actual_command));
    }

    void TestForNull(const std::shared_ptr<Command> actual_command) {
        EXPECT_EQ(nullptr, actual_command);
    }
};

TEST_F(CommandFactoryTests, CreateAddTaskCommand_ShouldCreateAddTaskCommand) {
    // Arrange
    context_.SetTaskBuilder(task_builder_);
    // Act
    std::shared_ptr<Command> actual_command = factory_.CreateAddTaskCommand(context_);
    // Assert
    TestCommandType<AddTaskCommand>(*actual_command);
}

TEST_F(CommandFactoryTests, CreateAddSubTaskCommand_ShouldCreateAddSubTaskCommand) {
    // Arrange
    context_.SetTaskBuilder(task_builder_);
    context_.SetTaskId(task_id_);
    // Act
    std::shared_ptr<Command> actual_command = factory_.CreateAddSubTaskCommand(context_);
    // Assert
    TestCommandType<AddSubTaskCommand>(*actual_command);
}

TEST_F(CommandFactoryTests, CreateAddSubTaskCommand_ShouldReturnNullptr) {
    // Arrange
    context_.SetTaskBuilder(task_builder_);
    // Act
    std::shared_ptr<Command> actual_command = factory_.CreateAddSubTaskCommand(context_);
    // Assert
    TestForNull(actual_command);
}

TEST_F(CommandFactoryTests, CreateEditCommand_ShouldCreateEditCommand) {
    // Arrange
    context_.SetTaskBuilder(task_builder_);
    context_.SetTaskId(task_id_);
    // Act
    std::shared_ptr<Command> actual_command = factory_.CreateEditCommand(context_);
    // Assert
    TestCommandType<EditTaskCommand>(*actual_command);
}

TEST_F(CommandFactoryTests, CreateEditCommand_ShouldReturnNullptr) {
    // Arrange
    context_.SetTaskBuilder(task_builder_);
    // Act
    std::shared_ptr<Command> actual_command = factory_.CreateEditCommand(context_);
    // Assert
    TestForNull(actual_command);
}

TEST_F(CommandFactoryTests, CreateCompleteCommand_ShouldCreateCompleteCommand) {
    // Arrange
    context_.SetTaskId(task_id_);
    // Act
    std::shared_ptr<Command> actual_command = factory_.CreateCompleteCommand(context_, true);
    // Assert
    TestCommandType<CompleteTaskCommand>(*actual_command);
}

TEST_F(CommandFactoryTests, CreateCompleteCommand_ShouldReturnNullptr) {
    // Act
    std::shared_ptr<Command> actual_command = factory_.CreateCompleteCommand(context_, false);
    // Assert
    TestForNull(actual_command);
}

TEST_F(CommandFactoryTests, CreateDeleteCommand_ShouldCreateDeleteCommand) {
    // Arrange
    context_.SetTaskId(task_id_);
    // Act
    std::shared_ptr<Command> actual_command = factory_.CreateDeleteCommand(context_, true);
    // Assert
    TestCommandType<DeleteTaskCommand>(*actual_command);
}

TEST_F(CommandFactoryTests, CreateDeleteCommand_ShouldReturnNullptr) {
    // Act
    std::shared_ptr<Command> actual_command = factory_.CreateDeleteCommand(context_, false);
    // Assert
    TestForNull(actual_command);
}

TEST_F(CommandFactoryTests, CreateSetLabelCommand_ShouldCreateSetLabelCommand) {
    // Arrange
    context_.SetTaskId(task_id_);
    // Act
    std::shared_ptr<Command> actual_command = factory_.CreateSetLabelCommand(context_);
    // Assert
    TestCommandType<SetLabelCommand>(*actual_command);
}

TEST_F(CommandFactoryTests, CreateSetLabelCommand_ShouldReturnNullptr) {
    // Act
    std::shared_ptr<Command> actual_command = factory_.CreateSetLabelCommand(context_);
    // Assert
    TestForNull(actual_command);
}

TEST_F(CommandFactoryTests, CreateRemoveLabelCommand_ShouldCreateRemoveLabelCommand) {
    // Arrange
    context_.SetTaskId(task_id_);
    // Act
    std::shared_ptr<Command> actual_command = factory_.CreateRemoveLabelCommand(context_);
    // Assert
    TestCommandType<RemoveLabelCommand>(*actual_command);
}

TEST_F(CommandFactoryTests, CreateRemoveLabelCommand_ShouldReturnNullptr) {
    // Act
    std::shared_ptr<Command> actual_command = factory_.CreateRemoveLabelCommand(context_);
    // Assert
    TestForNull(actual_command);
}

TEST_F(CommandFactoryTests, CreateShowCommand_ShouldCreateShowCommand) {
    // Act
    std::shared_ptr<Command> actual_command = factory_.CreateShowCommand(context_);
    // Assert
    TestCommandType<ShowTasksCommand>(*actual_command);
}

TEST_F(CommandFactoryTests, CreateSaveCommand_ShouldCreateSaveCommand) {
    // Arrange
    context_.SetFileName(file_name_);
    // Act
    std::shared_ptr<Command> actual_command = factory_.CreateSaveCommand(context_);
    // Assert
    TestCommandType<SaveCommand>(*actual_command);
}

TEST_F(CommandFactoryTests, CreateSaveCommand_ShouldReturnNullptr) {
    // Act
    std::shared_ptr<Command> actual_command = factory_.CreateSaveCommand(context_);
    // Assert
    TestForNull(actual_command);
}

TEST_F(CommandFactoryTests, CreateLoadCommand_ShouldCreateLoadCommand) {
    // Arrange
    context_.SetFileName(file_name_);
    // Act
    std::shared_ptr<Command> actual_command = factory_.CreateLoadCommand(context_);
    // Assert
    TestCommandType<LoadCommand>(*actual_command);
}

TEST_F(CommandFactoryTests, CreateLoadCommand_ShouldReturnNullptr) {
    // Act
    std::shared_ptr<Command> actual_command = factory_.CreateLoadCommand(context_);
    // Assert
    TestForNull(actual_command);
}
