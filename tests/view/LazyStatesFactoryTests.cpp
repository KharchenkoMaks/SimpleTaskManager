//
// Created by Maksym Kharchenko on 16.01.2022.
//

#include "gtest/gtest.h"

#include "view/states/factory/LazyStatesFactory.h"

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
#include "states/task_input/AddLabelState.h"
#include "states/persistence/SaveState.h"
#include "states/persistence/LoadState.h"
#include "states/ShowState.h"
#include "states/task_input/RemoveLabelState.h"

#include <typeinfo>

class LazyStatesFactoryTests : public ::testing::Test {
public:
    std::shared_ptr<StatesFactory> states_factory_;

    void SetUp() override {
        states_factory_ = std::make_shared<LazyStatesFactory>(nullptr, nullptr, nullptr);
    }

    template<class TStateType>
    void TestGetState(const StateType state_type) {
        auto& actual_state = *states_factory_->GetState(state_type);

        ASSERT_EQ(typeid(TStateType), typeid(actual_state));
    }
};

TEST_F(LazyStatesFactoryTests, GetState_ShouldReturnRightState) {
    TestGetState<RootState>(StateType::kRoot);
    TestGetState<HelpState>(StateType::kHelp);
    TestGetState<QuitState>(StateType::kQuit);
    TestGetState<AddTaskState>(StateType::kAddTask);
    TestGetState<AddSubTaskState>(StateType::kAddSubTask);
    TestGetState<EditTaskState>(StateType::kEditTask);
    TestGetState<InputTaskTitleState>(StateType::kInputTaskTitle);
    TestGetState<InputTaskPriorityState>(StateType::kInputTaskPriority);
    TestGetState<InputTaskDueDateState>(StateType::kInputTaskDueDate);
    TestGetState<CompleteTaskState>(StateType::kComplete);
    TestGetState<DeleteTaskState>(StateType::kDelete);
    TestGetState<AddLabelState>(StateType::kAddLabel);
    TestGetState<SaveState>(StateType::kSave);
    TestGetState<LoadState>(StateType::kLoad);
    TestGetState<ShowState>(StateType::kShow);
    TestGetState<RemoveLabelState>(StateType::kRemoveLabel);
    TestGetState<InputShowParametersState>(StateType::kInputShowParameters);
    TestGetState<InputShowByLabelState>(StateType::kInputShowTaskLabel);
}

TEST_F(LazyStatesFactoryTests, GetEndState_ShouldReturnNullptr) {
    // Arrange
    std::shared_ptr<State> expected_state = nullptr;
    // Act
    auto actual_state = states_factory_->GetState(StateType::kEnd);
    // Assert
    EXPECT_EQ(expected_state, actual_state);
}
