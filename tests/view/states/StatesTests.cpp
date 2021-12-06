//
// Created by Maksym Kharchenko on 03.12.2021.
//

#include "gtest/gtest.h"

#include "../mocks/MockWizardStatesFactory.h"
#include "../mocks/MockController.h"
#include "../mocks/MockConsolePrinter.h"
#include "../mocks/MockConsoleReader.h"
#include "../mocks/MockTaskValidator.h"
#include "../mocks/MockModel.h"
#include "../mocks/MockWizardContext.h"

using ::testing::Return;

class StatesTests : public ::testing::Test {
public:
    std::shared_ptr<MockConsolePrinter> printer_;
    std::shared_ptr<MockConsoleReader> reader_;
    std::shared_ptr<MockTaskValidator> task_validator_;
    std::shared_ptr<MockModel> model_;
    std::shared_ptr<MockController> controller_;
    std::shared_ptr<MockWizardStatesFactory> factory_;
    std::shared_ptr<MockWizardContext> context_;

    void SetUp() override {
        printer_ = std::make_shared<MockConsolePrinter>();
        reader_ = std::make_shared<MockConsoleReader>();
        task_validator_ = std::make_unique<MockTaskValidator>();
        model_ = std::make_unique<MockModel>();
        controller_ = std::make_shared<MockController>(std::make_unique<MockModel>(), std::make_unique<MockTaskValidator>());
        factory_ = std::make_shared<MockWizardStatesFactory>(controller_, printer_, reader_);
        context_ = std::make_shared<MockWizardContext>();
    };

};

// RootState receives nullopt from factory
// Should call GetNextState with MoveType::ERROR
TEST_F(StatesTests, ExecuteRootStateReceivesNulloptFromFactory_ShouldChangeStateToRoot) {
    // Arrange
    StatesTests::SetUp();
    RootState root_state(factory_, printer_, reader_);
    std::optional<std::shared_ptr<WizardStateConsole>> expected_return =
            std::make_shared<RootState>(factory_, printer_, reader_);
    // Assert
    // Invites user to input command
    EXPECT_CALL(*printer_, Write("> ")).Times(1);
    // Receives cmd
    EXPECT_CALL(*reader_, ReadLine())
            .Times(1)
            .WillOnce(Return("cmd"));
    // Gives received command to factory and receives nullopt
    EXPECT_CALL(*factory_, GetStateByCommand("cmd"))
        .Times(1)
        .WillOnce(Return(std::nullopt));
    // Writes error message and call next state with MoveType::ERROR
    EXPECT_CALL(*printer_, WriteError("Unknown command! Use help.")).Times(1);
    EXPECT_CALL(*factory_, GetNextState(testing::An<const RootState&>(), WizardStatesFactory::MoveType::ERROR))
        .Times(1)
        .WillOnce(Return(expected_return));
    // Act
    std::optional<std::shared_ptr<WizardStateConsole>> actual_return = root_state.Execute(context_);
    // Assert
    EXPECT_EQ(expected_return, actual_return);
}