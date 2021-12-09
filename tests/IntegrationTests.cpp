//
// Created by Maksym Kharchenko on 09.12.2021.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "view/mocks/MockConsolePrinter.h"
#include "view/mocks/MockConsoleReader.h"

#include "TaskManager.h"
#include "ConsoleStateMachine.h"
#include "states/factory/WizardStatesFactory.h"
#include "Controller.h"

using ::testing::Return;
using ::testing::InSequence;

class IntegrationTests : public ::testing::Test {

};

TEST_F(IntegrationTests, Script1) {
    // Arrange
    std::shared_ptr<MockConsolePrinter> printer_ = std::make_shared<MockConsolePrinter>();
    std::shared_ptr<MockConsoleReader> reader_ = std::make_shared<MockConsoleReader>();

    std::shared_ptr<Controller> controller =
            std::make_shared<Controller>(std::make_unique<TaskManager>(std::make_unique<IdGenerator>()),
                                         std::make_unique<TaskValidator>());
    std::shared_ptr<WizardStatesFactory> states_factory = std::make_shared<WizardStatesFactory>(controller,
                                                                                                printer_,
                                                                                                reader_);
    ConsoleStateMachine state_machine;

    std::string expected_show = "ID: 0, SomeTask, Priority: High, Due to: 16:30 01.01.2023, Completed: Yes\n";
    // Act
    EXPECT_CALL(*reader_, ReadLine())
            .WillOnce(Return("abc"))
            .WillOnce(Return("help"))
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
            .WillOnce(Return("0"))
            .WillOnce(Return("show"))
            .WillOnce(Return("quit"))
            .WillOnce(Return("y"));
    EXPECT_CALL(*printer_, WriteError(testing::_)).Times(testing::AnyNumber());
    EXPECT_CALL(*printer_, WriteLine(testing::_)).Times(testing::AnyNumber());
    {
        InSequence s;
        EXPECT_CALL(*printer_, Write(testing::_)).Times(16);
        EXPECT_CALL(*printer_, Write(expected_show)).Times(1);
        EXPECT_CALL(*printer_, Write(testing::_)).Times(2);
    }
    state_machine.Run(std::make_shared<WizardContext>(), states_factory->GetInitialState());
}