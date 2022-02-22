//
// Created by Maksym Kharchenko on 17.02.2022.
//

#include "gtest/gtest.h"

#include "model/TaskManager.h"

#include "view/commands/AddTaskCommand.h"
#include "view/commands/AddSubTaskCommand.h"
#include "view/commands/EditTaskCommand.h"
#include "view/commands/SetLabelCommand.h"

#include "controller/DefaultModelController.h"
#include "persistence/PersistenceFactory.h"

#include <google/protobuf/util/time_util.h>
#include <thread>

class DISABLED_HighLoadTaskManagerTest : public ::testing::Test {
public:
    std::shared_ptr<ModelController> model_controller_;

    void SetUp() override {
        model_controller_ = std::make_shared<DefaultModelController>(
                std::make_unique<TaskManager>(std::make_unique<IdGenerator>()),
                std::make_unique<TaskValidator>(),
                std::make_unique<persistence::PersistenceFactory>());
    }

    std::shared_ptr<Command> CreateRandomCommand() {
        int cmd_type = rand() % 4;
        TaskId id;
        id.set_id(rand() % 200);
        auto task = TaskBuilder::Create().SetTitle("task").SetPriority(Task::Priority::Task_Priority_MEDIUM).SetDueDate(google::protobuf::util::TimeUtil::TimeTToTimestamp(time(nullptr) + 10000));
        switch (cmd_type) {
            case 0:
                return std::make_shared<AddTaskCommand>(task.BuildTask());
            case 1:
                return std::make_shared<AddSubTaskCommand>(task.BuildTask(), id);
            case 2:
                return std::make_shared<EditTaskCommand>(task, id);
            case 3:
                return std::make_shared<SetLabelCommand>(id, "some label");
            default:
                return nullptr;
        }
    }

    void ExecuteRandomCommandToTaskManager(const int times) {
        for (int i = 0; i < times; ++i) {
            auto cmd = DISABLED_HighLoadTaskManagerTest::CreateRandomCommand();
            cmd->Execute(model_controller_);
        }
    }
};

TEST_F(DISABLED_HighLoadTaskManagerTest, SendingDifferentRequestsToTaskManagerInDifferentThreads_ShouldNotDie) {
    // Arrange
    const int thread_count = 8;
    const int commands_per_thread = 1000;

    std::vector<std::thread> threads;
    // Act
    for (int i = 0; i < thread_count; ++i) {
        std::thread t {&DISABLED_HighLoadTaskManagerTest::ExecuteRandomCommandToTaskManager, this, commands_per_thread };
        threads.push_back(std::move(t));
    }

    for (auto& thread : threads) {
        thread.join();
    }
}
