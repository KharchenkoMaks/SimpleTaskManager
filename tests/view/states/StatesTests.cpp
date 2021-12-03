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

using ::testing::Return;

class StatesTests : public ::testing::Test {
public:
    std::shared_ptr<MockConsolePrinter> printer_;
    std::shared_ptr<MockConsoleReader> reader_;
    std::shared_ptr<MockTaskValidator> task_validator_;
    std::shared_ptr<MockModel> model_;
    std::shared_ptr<MockController> controller_;
    std::shared_ptr<MockWizardStatesFactory> factory_;

    void SetUp() override {
        printer_ = std::make_shared<MockConsolePrinter>();
        reader_ = std::make_shared<MockConsoleReader>();
        task_validator_ = std::make_unique<MockTaskValidator>();
        model_ = std::make_unique<MockModel>();
        controller_ = std::make_shared<MockController>(std::make_unique<MockModel>(), std::make_unique<MockTaskValidator>());
        factory_ = std::make_shared<MockWizardStatesFactory>(controller_, printer_, reader_);
    };

};

TEST_F(StatesTests, InputtingCommandsInRootState_ShouldCallStatesFactoryGetStateByCommandMethod) {
    // Arrange
    StatesTests::SetUp();
    RootState root_state(factory_, printer_, reader_);
    EXPECT_CALL(*factory_, GetStateByCommand(testing::_))
        .Times(1)
        .WillOnce(Return(std::nullopt));
    EXPECT_CALL(*printer_, Write("> ")).Times(1);
    EXPECT_CALL(*reader_, ReadLine())
            .Times(1)
            .WillOnce(Return("add"));
    EXPECT_CALL(*printer_, WriteError("Unknown command! Use help.")).Times(1);
    EXPECT_CALL(*factory_, GetNextState(testing::An<const RootState&>(), WizardStatesFactory::MoveType::ERROR)).Times(1);
    // TODO: Make MockWizardContext
    root_state.Execute(std::make_shared<WizardContext>());
}