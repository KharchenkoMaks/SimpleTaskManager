//
// Created by Maksym Kharchenko on 09.12.2021.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "view/mocks/MockConsolePrinter.h"
#include "view/mocks/MockConsoleReader.h"

#include "TaskManager.h"
#include "states/factory/StatesFactory.h"
#include "Controller.h"
#include <user_interface/UserInterface.h>
#include <ViewController.h>

using ::testing::Return;
using ::testing::InSequence;

class IntegrationTests : public ::testing::Test {

};

TEST_F(IntegrationTests, Script1) {
    // Arrange
    std::string expected_show = "ID: 0, SomeTask, Priority: High, Due to: 16:30 01.01.2023, Completed: Yes";
    // Assert
    std::unique_ptr<MockConsolePrinter> printer_ = std::make_unique<MockConsolePrinter>();
    std::unique_ptr<MockConsoleReader> reader_ = std::make_unique<MockConsoleReader>();

    EXPECT_CALL(*reader_, ReadLine())
            .WillOnce(Return("abc"))
            .WillOnce(Return("complete"))
            .WillOnce(Return("1"))
            .WillOnce(Return(""))
            .WillOnce(Return("add"))
            .WillOnce(Return("SomeTask"))
            .WillOnce(Return("Ne xo4y"))
            .WillOnce(Return("4"))
            .WillOnce(Return("High"))
            .WillOnce(Return("15:00"))
            .WillOnce(Return("16:30 01.01.2023"))
            .WillOnce(Return("complete"))
            .WillOnce(Return("5"))
            .WillOnce(Return("y"))
            .WillOnce(Return("complete"))
            .WillOnce(Return("0"))
            .WillOnce(Return("y"))
            .WillOnce(Return("show"))
            .WillOnce(Return("quit"))
            .WillOnce(Return("y"));
    EXPECT_CALL(*printer_, WriteError(testing::_)).Times(testing::AnyNumber());
    EXPECT_CALL(*printer_, Write(testing::_)).Times(testing::AnyNumber());

    EXPECT_CALL(*printer_, WriteLine(testing::_)).Times(testing::AnyNumber());
    EXPECT_CALL(*printer_, WriteLine(expected_show)).Times(1);
    // Arrange
    std::shared_ptr<CommandFactory> command_factory = std::make_shared<CommandFactory>();
    std::shared_ptr<StatesFactory> states_factory = std::make_shared<StatesFactory>(command_factory,
                                                                                    std::move(printer_),
                                                                                    std::move(reader_));
    std::unique_ptr<UserInterface> user_interface = std::make_unique<UserInterface>(
            states_factory);
    std::unique_ptr<Controller> model_controller = std::make_unique<Controller>(
            std::make_unique<TaskManager>(std::make_unique<IdGenerator>()),
            std::make_unique<TaskValidator>());
    std::unique_ptr<ViewController> view_controller = std::make_unique<ViewController>(
            std::move(model_controller),
            std::move(user_interface));
    // Act
    view_controller->RunUserInterface();
}