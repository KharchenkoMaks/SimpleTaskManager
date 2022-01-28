//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "StatesFactory.h"

#include "states/RootState.h"
#include "states/HelpState.h"
#include "states/QuitState.h"
#include "states/task_input/AddTaskState.h"
#include "states/task_input/EditTaskState.h"
#include "states/task_input/InputTaskTitleState.h"
#include "states/task_input/InputTaskPriorityState.h"
#include "states/task_input/InputTaskDueDateState.h"
#include "states/InputShowParametersState.h"
#include "states/CompleteTaskState.h"
#include "states/task_input/AddSubTaskState.h"
#include "states/DeleteTaskState.h"
#include "states/task_input/SetLabelState.h"
#include "states/task_input/RemoveLabelState.h"
#include "states/EndState.h"
#include "states/persistence/SaveState.h"
#include "states/persistence/LoadState.h"
#include "states/ShowState.h"

StatesFactory::StatesFactory(const std::shared_ptr<CommandFactory>& command_factory,
                             const std::shared_ptr<ConsolePrinter>& printer,
                             const std::shared_ptr<ConsoleReader>& reader) :
                             command_factory_(command_factory),
                             printer_(printer),
                             reader_(reader) {}

std::shared_ptr<State> StatesFactory::GetState(StateType state) {
    auto found_state = states_.find(state);
    if (found_state == states_.end()) {
        InitializeState(state);
        found_state = states_.find(state);
    }
    return found_state->second;
}

void StatesFactory::InitializeState(StateType state) {
    switch (state) {
        case StateType::kRoot:
            states_.insert_or_assign(state, std::make_shared<RootState>(shared_from_this()));
            break;
        case StateType::kHelp:
            states_.insert_or_assign(state, std::make_shared<HelpState>(shared_from_this()));
            break;
        case StateType::kQuit:
            states_.insert_or_assign(state, std::make_shared<QuitState>(shared_from_this()));
            break;
        case StateType::kAddTask:
            states_.insert_or_assign(state, std::make_shared<AddTaskState>(shared_from_this()));
            break;
        case StateType::kAddSubTask:
            states_.insert_or_assign(state, std::make_shared<AddSubTaskState>(shared_from_this()));
            break;
        case StateType::kEditTask:
            states_.insert_or_assign(state, std::make_shared<EditTaskState>(shared_from_this()));
            break;
        case StateType::kInputTaskTitle:
            states_.insert_or_assign(state, std::make_shared<InputTaskTitleState>(shared_from_this()));
            break;
        case StateType::kInputTaskPriority:
            states_.insert_or_assign(state, std::make_shared<InputTaskPriorityState>(shared_from_this()));
            break;
        case StateType::kInputTaskDueDate:
            states_.insert_or_assign(state, std::make_shared<InputTaskDueDateState>(shared_from_this()));
            break;
        case StateType::kInputShowParameters:
            states_.insert_or_assign(state, std::make_shared<InputShowParametersState>(shared_from_this()));
            break;
        case StateType::kComplete:
            states_.insert_or_assign(state, std::make_shared<CompleteTaskState>(shared_from_this()));
            break;
        case StateType::kDelete:
            states_.insert_or_assign(state, std::make_shared<DeleteTaskState>(shared_from_this()));
            break;
        case StateType::kSetLabel:
            states_.insert_or_assign(state, std::make_shared<SetLabelState>(shared_from_this()));
            break;
        case StateType::kRemoveLabel:
            states_.insert_or_assign(state, std::make_shared<RemoveLabelState>(shared_from_this()));
            break;
        case StateType::kEnd:
            states_.insert_or_assign(state, std::make_shared<EndState>(shared_from_this()));
            break;
        case StateType::kSave:
            states_.insert_or_assign(state, std::make_shared<SaveState>(shared_from_this()));
            break;
        case StateType::kLoad:
            states_.insert_or_assign(state, std::make_shared<LoadState>(shared_from_this()));
            break;
        case StateType::kShow:
            states_.insert_or_assign(state, std::make_shared<ShowState>(shared_from_this()));
            break;
    }
}

std::unique_ptr<ConsoleStateMachine> StatesFactory::CreateStateMachine(const StateType initial_state,
                                                                       const std::shared_ptr<StateContext>& context) {
    return std::make_unique<ConsoleStateMachine>(GetState(initial_state), context);
}
