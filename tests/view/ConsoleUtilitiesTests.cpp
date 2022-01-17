//
// Created by Maksym Kharchenko on 17.01.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "mocks/MockConsolePrinter.h"
#include "mocks/MockConsoleReader.h"

#include "view/user_interface/console_io/ConsoleUtilities.h"

#include "utilities/TaskComparators.h"

using ::testing::Return;

class ConsoleUtilitiesTests : public ::testing::Test {

};

TEST_F(ConsoleUtilitiesTests, GetUserInput_ShouldReturnUserInput) {
    // Arrange
    const std::string expected_invitational_string = "print here";
    const std::string expected_user_input = "user input text";

    MockConsoleReader reader;
    MockConsolePrinter printer;

    EXPECT_CALL(printer, Write(expected_invitational_string + "> ")).Times(1);
    EXPECT_CALL(reader, ReadLine()).WillOnce(Return(expected_user_input));
    // Act
    const std::string actual_user_input = console_io::util::GetUserInput(expected_invitational_string, printer, reader);
    // Assert
    EXPECT_EQ(expected_user_input, actual_user_input);
}

TEST_F(ConsoleUtilitiesTests, UserConfirm_ShouldReturnTrueOnUserConfirmation) {
    // Arrange
    const std::string expected_invitational_string = "print here";
    const std::string expected_user_input = "y";
    const bool expected_user_confirmation = true;

    MockConsoleReader reader;
    MockConsolePrinter printer;

    EXPECT_CALL(printer, Write(expected_invitational_string + " y/n" + "> ")).Times(1);
    EXPECT_CALL(reader, ReadLine()).WillOnce(Return(expected_user_input));
    // Act
    const bool actual_user_confirmation = console_io::util::UserConfirm(expected_invitational_string, printer, reader);
    // Assert
    EXPECT_EQ(expected_user_confirmation, actual_user_confirmation);
}

TEST_F(ConsoleUtilitiesTests, UserConfirm_ShouldReturnFalseOnUserConfirmation) {
    // Arrange
    const std::string expected_invitational_string = "print here";
    const std::string expected_user_input = "n";
    const bool expected_user_confirmation = false;

    MockConsoleReader reader;
    MockConsolePrinter printer;

    EXPECT_CALL(printer, Write(expected_invitational_string + " y/n" + "> ")).Times(1);
    EXPECT_CALL(reader, ReadLine()).WillOnce(Return(expected_user_input));
    // Act
    const bool actual_user_confirmation = console_io::util::UserConfirm(expected_invitational_string, printer, reader);
    // Assert
    EXPECT_EQ(expected_user_confirmation, actual_user_confirmation);
}

TEST_F(ConsoleUtilitiesTests, GetTaskIdFromUser_ShouldReturnUsersTaskId) {
    // Arrange
    const std::string expected_invitational_string = "print here";
    const std::string expected_user_input = "10";
    TaskId expected_task_id;
    expected_task_id.set_id(std::stoi(expected_user_input));

    MockConsoleReader reader;
    MockConsolePrinter printer;

    EXPECT_CALL(printer, Write(expected_invitational_string + "> ")).Times(1);
    EXPECT_CALL(reader, ReadLine()).WillOnce(Return(expected_user_input));
    // Act
    const std::optional<TaskId> actual_user_task_id = console_io::util::GetTaskIdFromUser(expected_invitational_string, printer, reader);
    // Assert
    ASSERT_NE(std::nullopt, actual_user_task_id);
    EXPECT_EQ(expected_task_id, actual_user_task_id.value());
}
