//
// Created by Maksym Kharchenko on 13.12.2021.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "states/ShowState.h"

#include "../mocks/MockStateDependencies.h"
#include "../mocks/MockWizardContext.h"
#include "../mocks/MockConsolePrinter.h"
#include "../mocks/MockWizardStatesFactory.h"
#include "../mocks/MockController.h"

#include <vector>
#include <utility>

using ::testing::Return;

class ShowStateTest : public ::testing::Test {
public:
    std::unique_ptr<MockStateDependencies> dependencies_;
    std::shared_ptr<MockWizardContext> wizard_context_;
    std::shared_ptr<MockConsolePrinter> printer_;
    std::shared_ptr<MockWizardStatesFactory> factory_;
    std::shared_ptr<MockController> controller_;
    void SetUp() override {
        dependencies_ = std::make_unique<MockStateDependencies>();
        wizard_context_ = std::make_shared<MockWizardContext>();
        printer_ = std::make_shared<MockConsolePrinter>();
        factory_ = std::make_shared<MockWizardStatesFactory>();
        controller_ = std::make_shared<MockController>();

        EXPECT_CALL(*dependencies_, GetConsolePrinter())
            .WillRepeatedly(testing::Return(printer_));
        EXPECT_CALL(*dependencies_, GetStatesFactory()).WillRepeatedly(Return(factory_));
        EXPECT_CALL(*dependencies_, GetController()).WillRepeatedly(Return(controller_));
    }
    void Test(const std::vector<std::string>& prints,
              const WizardStatesFactory::MoveType move_type,
              const std::shared_ptr<WizardStateInterface>& expected_next_state) {
        for (const auto& print : prints) {
            EXPECT_CALL(*printer_, WriteLine(print)).Times(1);
        }

        EXPECT_CALL(*factory_, GetNextState(testing::An<const ShowState&>(), move_type))
            .Times(1)
            .WillOnce(Return(expected_next_state));

        ShowState show_state { std::move(dependencies_) };
        const std::shared_ptr<WizardStateInterface> actual_next_state = show_state.Execute(wizard_context_);
        EXPECT_EQ(expected_next_state, actual_next_state);
    }
};

TEST_F(ShowStateTest, Execute_ShouldPrintTasksReceivedFromController) {
    const TaskId parent_task_id = TaskId::Create(0).value();
    const std::pair<TaskId, Task> task1 = std::make_pair(parent_task_id, Task::Create("task1", Task::Priority::LOW, DueTime::Create(100)));
    const std::pair<TaskId, Task> task2 = std::make_pair(TaskId::Create(1).value(), Task::Create("task2", Task::Priority::MEDIUM, DueTime::Create(100)));
    const std::pair<TaskId, Task> subtask = std::make_pair(TaskId::Create(1).value(), Task::Create("subtask", Task::Priority::MEDIUM, DueTime::Create(100)));
    const std::vector<std::string> prints {
        task1.first.to_string() + ", " + task1.second.to_string(),
        "\t" + subtask.first.to_string() + ", " + subtask.second.to_string(),
        task2.first.to_string() + ", " + task2.second.to_string()
    };
    const std::vector<TaskTransfer> returned_tasks_from_controller {
        TaskTransfer::Create(task1.first, task1.second),
        TaskTransfer::Create(subtask.first, subtask.second, parent_task_id),
        TaskTransfer::Create(task2.first, task2.second)
    };
    EXPECT_CALL(*controller_, GetAllTasks()).Times(1).WillOnce(Return(returned_tasks_from_controller));
    Test(prints, WizardStatesFactory::MoveType::NEXT, std::make_shared<RootState>(nullptr));
}