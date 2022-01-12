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

class DISABLED_IntegrationTests : public ::testing::Test {
public:
    void LaunchTest(const std::vector<std::string>& expected_show,
                    const std::vector<std::string>& inputs) {
        std::unique_ptr<MockConsolePrinter> printer_ = std::make_unique<MockConsolePrinter>();
        std::unique_ptr<MockConsoleReader> reader_ = std::make_unique<MockConsoleReader>();
        {
            InSequence s;
            for (const std::string &input: inputs) {
                EXPECT_CALL(*reader_, ReadLine()).WillOnce(Return(input));
            }
            EXPECT_CALL(*reader_, ReadLine())
                .WillOnce(Return("show"))
                .WillOnce(Return("quit"))
                .WillOnce(Return("y"));
        }
        EXPECT_CALL(*printer_, WriteError(testing::_)).Times(testing::AnyNumber());
        EXPECT_CALL(*printer_, Write(testing::_)).Times(testing::AnyNumber());

        EXPECT_CALL(*printer_, WriteLine(testing::_)).Times(testing::AnyNumber());
        {
            InSequence s;
            for (const std::string& show : expected_show) {
                EXPECT_CALL(*printer_, WriteLine(show)).Times(1);
            }
        }
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
};

TEST_F(DISABLED_IntegrationTests, Script1) {
    // Arrange
    std::vector<std::string> inputs = {
            "qwe",
            "complete",
            "1",
            "",
            "add",
            "SomeTask",
            "Ne xo4y",
            "4",
            "High",
            "15:00",
            "16:30 01.01.2023",
            "complete",
            "5",
            "y",
            "complete",
            "1",
            "y"
    };
    std::vector<std::string> expected_show = { "ID: 1, SomeTask, Priority: High, Due to: 16:30 01.01.2023, Completed: Yes" };
    // Act
    LaunchTest(expected_show, inputs);
}

TEST_F(DISABLED_IntegrationTests, Script2) {
    // Arrange
    std::vector<std::string> inputs = {
            "add",
            "First task",
            "Low",
            "01.02.2025",
            "add_subtask",
            "1",
            "Subtask",
            "None",
            "15:00 15.01.2025",
            "add_subtask",
            "1",
            "Second Subtask",
            "High",
            "15:00 15.01.2025",
            "complete",
            "1",
            "n",
            "complete",
            "3",
            "n",
    };
    std::vector<std::string> expected_show = {
            "ID: 1, First task, Priority: Low, Due to: 00:00 01.02.2025, Completed: No",
            "\tID: 2, Subtask, Priority: None, Due to: 15:00 15.01.2025, Completed: No",
            "\tID: 3, Second Subtask, Priority: High, Due to: 15:00 15.01.2025, Completed: Yes"
    };
    // Act
    LaunchTest(expected_show, inputs);
}