//
// Created by Maksym Kharchenko on 10.01.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Task.pb.h"

#include "mocks/MockStatesFactory.h"
#include "mocks/MockCommandFactory.h"
#include "mocks/MockConsolePrinter.h"
#include "mocks/MockConsoleReader.h"

using ::testing::Return;

class StatesTests : public ::testing::Test {
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
    void ExpectGetUserInput(const std::string& message, const std::string& returned_input) {
        EXPECT_CALL(*console_printer_, Write(message + "> ")).Times(1);
        EXPECT_CALL(*console_reader_, ReadLine()).WillOnce(Return(returned_input));
    }
};