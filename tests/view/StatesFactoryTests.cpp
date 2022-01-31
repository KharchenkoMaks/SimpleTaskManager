//
// Created by Maksym Kharchenko on 16.01.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "view/states/factory/StatesFactory.h"

#include "states/RootState.h"
#include "states/HelpState.h"
#include "states/QuitState.h"
#include "states/task_input/AddTaskState.h"
#include "states/task_input/EditTaskState.h"
#include "states/task_input/InputTaskTitleState.h"
#include "states/task_input/InputTaskPriorityState.h"
#include "states/task_input/InputTaskDueDateState.h"
#include "states/InputShowParametersState.h"
#include "states/InputShowByLabelState.h"
#include "states/CompleteTaskState.h"
#include "states/task_input/AddSubTaskState.h"
#include "states/DeleteTaskState.h"
#include "states/task_input/SetLabelState.h"
#include "states/EndState.h"
#include "states/persistence/SaveState.h"
#include "states/persistence/LoadState.h"
#include "states/ShowState.h"
#include "states/task_input/RemoveLabelState.h"

#include <typeinfo>

class StatesFactoryTests : public ::testing::Test {
public:
    template<class TTesting, class TPrev, class TError, class TNext>
    void TestGetNextState() {
        TTesting testing_state(nullptr);
        std::shared_ptr<StatesFactory> states_factory = std::make_shared<StatesFactory>(nullptr, nullptr, nullptr);

        auto& actual_prev_state =
                *states_factory->GetNextState(testing_state, StatesFactory::MoveType::PREVIOUS);
        auto& actual_error_state =
                *states_factory->GetNextState(testing_state, StatesFactory::MoveType::ERROR);
        auto& actual_next_state =
                *states_factory->GetNextState(testing_state, StatesFactory::MoveType::NEXT);

        EXPECT_EQ(typeid(TPrev), typeid(actual_prev_state));
        EXPECT_EQ(typeid(TError), typeid(actual_error_state));
        EXPECT_EQ(typeid(TNext), typeid(actual_next_state));
    }
};

TEST_F(StatesFactoryTests, GetNextStateOfQuitState) {
    TestGetNextState<QuitState, RootState, RootState, EndState>();
}

TEST_F(StatesFactoryTests, GetNextStateOfAddTaskState) {
    TestGetNextState<AddTaskState, EndState, RootState, InputTaskTitleState>();
}

TEST_F(StatesFactoryTests, GetNextStateOfAddSubTaskState) {
    TestGetNextState<AddSubTaskState, EndState, RootState, InputTaskTitleState>();
}

TEST_F(StatesFactoryTests, GetNextStateOfEditTaskState) {
    TestGetNextState<EditTaskState, EndState, RootState, InputTaskTitleState>();
}

TEST_F(StatesFactoryTests, GetNextStateOfInputTaskTitleState) {
    TestGetNextState<InputTaskTitleState, InputTaskTitleState, InputTaskTitleState, InputTaskPriorityState>();
}

TEST_F(StatesFactoryTests, GetNextStateOfInputTaskPriorityState) {
    TestGetNextState<InputTaskPriorityState, InputTaskTitleState, InputTaskPriorityState, InputTaskDueDateState>();
}

TEST_F(StatesFactoryTests, GetNextStateOfInputTaskDueDateState) {
    TestGetNextState<InputTaskDueDateState, InputTaskPriorityState, InputTaskDueDateState, EndState>();
}

TEST_F(StatesFactoryTests, GetNextStateOfHelpStateState) {
    TestGetNextState<HelpState, RootState, RootState, RootState>();
}

TEST_F(StatesFactoryTests, GetNextStateOfRootState) {
    TestGetNextState<RootState, RootState, RootState, RootState>();
}

TEST_F(StatesFactoryTests, GetNextStateOfInputShowParametersState) {
    TestGetNextState<InputShowParametersState, EndState, EndState, EndState>();
}

TEST_F(StatesFactoryTests, GetNextStateOfInputShowByLabelStateState) {
    TestGetNextState<InputShowByLabelState, EndState, EndState, EndState>();
}

TEST_F(StatesFactoryTests, GetNextStateOfCompleteState) {
    TestGetNextState<CompleteTaskState, EndState, CompleteTaskState, EndState>();
}

TEST_F(StatesFactoryTests, GetNextStateOfDeleteTaskState) {
    TestGetNextState<DeleteTaskState, EndState, DeleteTaskState, EndState>();
}

TEST_F(StatesFactoryTests, GetNextStateOfSetLabelState) {
    TestGetNextState<SetLabelState, EndState, SetLabelState, EndState>();
}

TEST_F(StatesFactoryTests, GetNextStateOfRemoveLabelState) {
    TestGetNextState<RemoveLabelState, EndState, RemoveLabelState, EndState>();
}

TEST_F(StatesFactoryTests, GetNextStateOfSaveState) {
    TestGetNextState<SaveState, EndState, RootState, EndState>();
}

TEST_F(StatesFactoryTests, GetNextStateOfLoadState) {
    TestGetNextState<LoadState, EndState, RootState, EndState>();
}

TEST_F(StatesFactoryTests, GetNextStateOfShowState) {
    TestGetNextState<ShowState, EndState, EndState, EndState>();
}

TEST_F(StatesFactoryTests, GetRootState_ShouldReturnRootState) {
    std::shared_ptr<StatesFactory> states_factory = std::make_shared<StatesFactory>(nullptr, nullptr, nullptr);

    auto& actual_root_state = *states_factory->GetRootState();

    EXPECT_EQ(typeid(RootState), typeid(actual_root_state));
}

TEST_F(StatesFactoryTests, GetShowState_ShouldReturnShowState) {
    // Arrange
    std::shared_ptr<StatesFactory> states_factory = std::make_shared<StatesFactory>(nullptr, nullptr, nullptr);
    // Act
    auto& actual_show_state = *states_factory->GetShowState();
    // Assert
    EXPECT_EQ(typeid(ShowState), typeid(actual_show_state));
}

TEST_F(StatesFactoryTests, GetStateByCommand_ShouldReturnRightStates) {
    // Arrange
    std::shared_ptr<StatesFactory> states_factory = std::make_shared<StatesFactory>(nullptr, nullptr, nullptr);

    const std::vector<std::string> expected_commands {
        "add",
        "add_subtask",
        "edit",
        "delete",
        "complete",
        "show",
        "help",
        "quit",
        "add_label",
        "remove_label",
        "save",
        "load"
    };
    const std::vector<std::shared_ptr<State>> expected_states {
        std::make_shared<AddTaskState>(nullptr),
        std::make_shared<AddSubTaskState>(nullptr),
        std::make_shared<EditTaskState>(nullptr),
        std::make_shared<DeleteTaskState>(nullptr),
        std::make_shared<CompleteTaskState>(nullptr),
        std::make_shared<InputShowParametersState>(nullptr),
        std::make_shared<HelpState>(nullptr),
        std::make_shared<QuitState>(nullptr),
        std::make_shared<SetLabelState>(nullptr),
        std::make_shared<RemoveLabelState>(nullptr),
        std::make_shared<SaveState>(nullptr),
        std::make_shared<LoadState>(nullptr)
    };
    // Act * Assert
    for (int i = 0; i < expected_commands.size(); ++i) {
        auto& expected_state = *expected_states[i];
        auto& actual_state = *states_factory->GetStateByCommand(expected_commands[i]);
        EXPECT_EQ(typeid(expected_state), typeid(actual_state));
    }
}

TEST_F(StatesFactoryTests, GetStateByCommand_ShouldReturnNullptrOnWrongCommand) {
    // Arrange
    std::shared_ptr<StatesFactory> states_factory = std::make_shared<StatesFactory>(nullptr, nullptr, nullptr);

    const std::string expected_command = "non existent command";
    const std::shared_ptr<State> expected_result = nullptr;
    // Act
    const std::shared_ptr<State> actual_result = states_factory->GetStateByCommand(expected_command);
    // Assert
    EXPECT_EQ(expected_result, actual_result);
}
