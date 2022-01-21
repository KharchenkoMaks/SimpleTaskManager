//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "StatesFactory.h"
#include "user_interface/ConsoleStateMachine.h"

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

std::shared_ptr<State> StatesFactory::GetStateByCommand(const std::string &command) {
    if (command == "add") {
        return GetLazyStateByStatesEnum(States::kAddTask);
    } else if (command == "add_subtask") {
        return GetLazyStateByStatesEnum(States::kAddSubTask);
    } else if (command == "edit") {
        return GetLazyStateByStatesEnum(States::kEditTask);
    } else if (command == "delete") {
        return GetLazyStateByStatesEnum(States::kDelete);
    } else if (command == "complete") {
        return GetLazyStateByStatesEnum(States::kComplete);
    } else if (command == "show") {
        return GetLazyStateByStatesEnum(States::kInputShowParameters);
    } else if (command == "help") {
        return GetLazyStateByStatesEnum(States::kHelp);
    } else if (command == "quit") {
        return GetLazyStateByStatesEnum(States::kQuit);
    } else if (command == "label") {
        return GetLazyStateByStatesEnum(States::kSetLabel);
    } else if (command == "save") {
        return GetLazyStateByStatesEnum(States::kSave);
    } else if (command == "load") {
        return GetLazyStateByStatesEnum(States::kLoad);
    } else {
        return nullptr;
    }
}

std::shared_ptr<State> StatesFactory::GetRootState() {
    return GetLazyStateByStatesEnum(States::kRoot);
}

std::shared_ptr<State> StatesFactory::GetShowState() {
    return GetLazyStateByStatesEnum(States::kShow);
}

std::shared_ptr<State> StatesFactory::GetNextState(const QuitState& state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::PREVIOUS:
            return GetLazyStateByStatesEnum(States::kRoot);
        case MoveType::ERROR:
            return GetLazyStateByStatesEnum(States::kRoot);
        case MoveType::NEXT:
            return GetLazyStateByStatesEnum(States::kEnd);
    }
}

std::shared_ptr<State> StatesFactory::GetNextState(const AddTaskState &state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::PREVIOUS:
            return GetLazyStateByStatesEnum(States::kEnd);
        case MoveType::ERROR:
            return GetLazyStateByStatesEnum(States::kRoot);
        case MoveType::NEXT:
            return GetLazyStateByStatesEnum(States::kInputTaskTitle);
    }
}

std::shared_ptr<State> StatesFactory::GetNextState(const AddSubTaskState& state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::PREVIOUS:
            return GetLazyStateByStatesEnum(States::kEnd);
        case MoveType::ERROR:
            return GetLazyStateByStatesEnum(States::kRoot);
        case MoveType::NEXT:
            return GetLazyStateByStatesEnum(States::kInputTaskTitle);
    }
}

std::shared_ptr<State> StatesFactory::GetNextState(const EditTaskState &state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::PREVIOUS:
            return GetLazyStateByStatesEnum(States::kEnd);
        case MoveType::ERROR:
            return GetLazyStateByStatesEnum(States::kRoot);
        case MoveType::NEXT:
            return GetLazyStateByStatesEnum(States::kInputTaskTitle);
    }
}

std::shared_ptr<State> StatesFactory::GetNextState(const InputTaskTitleState &state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::NEXT:
            return GetLazyStateByStatesEnum(States::kInputTaskPriority);
        default:
            return GetLazyStateByStatesEnum(States::kInputTaskTitle);
    }
}

std::shared_ptr<State> StatesFactory::GetNextState(const InputTaskPriorityState &state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::PREVIOUS:
            return GetLazyStateByStatesEnum(States::kInputTaskTitle);
        case MoveType::ERROR:
            return GetLazyStateByStatesEnum(States::kInputTaskPriority);
        case MoveType::NEXT:
            return GetLazyStateByStatesEnum(States::kInputTaskDueDate);
    }
}

std::shared_ptr<State> StatesFactory::GetNextState(const InputTaskDueDateState &state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::PREVIOUS:
            return GetLazyStateByStatesEnum(States::kInputTaskPriority);
        case MoveType::ERROR:
            return GetLazyStateByStatesEnum(States::kInputTaskDueDate);
        case MoveType::NEXT:
            return GetLazyStateByStatesEnum(States::kEnd);
    }
}

std::shared_ptr<State> StatesFactory::GetNextState(const HelpState &state, MoveType move_type) {
    return GetLazyStateByStatesEnum(States::kRoot);
}

std::shared_ptr<State> StatesFactory::GetNextState(const RootState &state, StatesFactory::MoveType move_type) {
    return GetLazyStateByStatesEnum(States::kRoot);
}

std::shared_ptr<State> StatesFactory::GetNextState(const InputShowParametersState &state, StatesFactory::MoveType move_type) {
    return GetLazyStateByStatesEnum(States::kEnd);
}

std::shared_ptr<State> StatesFactory::GetNextState(const CompleteTaskState &state, StatesFactory::MoveType move_type) {
    switch (move_type) {
        case MoveType::ERROR:
            return GetLazyStateByStatesEnum(States::kComplete);
        default:
            return GetLazyStateByStatesEnum(States::kEnd);
    }
}

std::shared_ptr<State> StatesFactory::GetNextState(const DeleteTaskState& state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::ERROR:
            return GetLazyStateByStatesEnum(States::kDelete);
        default:
            return GetLazyStateByStatesEnum(States::kEnd);
    }
}

std::shared_ptr<State> StatesFactory::GetNextState(const SetLabelState &state, const StatesFactory::MoveType move_type) {
    switch (move_type) {
        case MoveType::ERROR:
            return GetLazyStateByStatesEnum(States::kSetLabel);
        default:
            return GetLazyStateByStatesEnum(States::kEnd);
    }
}

std::shared_ptr<State> StatesFactory::GetNextState(const SaveState &state, const StatesFactory::MoveType move_type) {
    switch(move_type) {
        case MoveType::ERROR:
            return GetLazyStateByStatesEnum(States::kRoot);
        default:
            return GetLazyStateByStatesEnum(States::kEnd);
    }
}

std::shared_ptr<State> StatesFactory::GetNextState(const LoadState &state, const StatesFactory::MoveType move_type) {
    switch(move_type) {
        case MoveType::ERROR:
            return GetLazyStateByStatesEnum(States::kRoot);
        default:
            return GetLazyStateByStatesEnum(States::kEnd);
    }
}

std::shared_ptr<State> StatesFactory::GetNextState(const ShowState& state, StatesFactory::MoveType move_type) {
    return GetLazyStateByStatesEnum(States::kEnd);
}

std::shared_ptr<State> StatesFactory::GetLazyStateByStatesEnum(StatesFactory::States state) {
    auto found_state = states_.find(state);
    if (found_state == states_.end()) {
        InitializeState(state);
        found_state = states_.find(state);
    }
    return found_state->second;
}

void StatesFactory::InitializeState(States state) {
    switch (state) {
        case States::kRoot:
            states_.insert_or_assign(state, std::make_shared<RootState>(CreateStatesFactory()));
            break;
        case States::kHelp:
            states_.insert_or_assign(state, std::make_shared<HelpState>(CreateStatesFactory()));
            break;
        case States::kQuit:
            states_.insert_or_assign(state, std::make_shared<QuitState>(CreateStatesFactory()));
            break;
        case States::kAddTask:
            states_.insert_or_assign(state, std::make_shared<AddTaskState>(CreateStatesFactory()));
            break;
        case States::kAddSubTask:
            states_.insert_or_assign(state, std::make_shared<AddSubTaskState>(CreateStatesFactory()));
            break;
        case States::kEditTask:
            states_.insert_or_assign(state, std::make_shared<EditTaskState>(CreateStatesFactory()));
            break;
        case States::kInputTaskTitle:
            states_.insert_or_assign(state, std::make_shared<InputTaskTitleState>(CreateStatesFactory()));
            break;
        case States::kInputTaskPriority:
            states_.insert_or_assign(state, std::make_shared<InputTaskPriorityState>(CreateStatesFactory()));
            break;
        case States::kInputTaskDueDate:
            states_.insert_or_assign(state, std::make_shared<InputTaskDueDateState>(CreateStatesFactory()));
            break;
        case States::kInputShowParameters:
            states_.insert_or_assign(state, std::make_shared<InputShowParametersState>(CreateStatesFactory()));
            break;
        case States::kComplete:
            states_.insert_or_assign(state, std::make_shared<CompleteTaskState>(CreateStatesFactory()));
            break;
        case States::kDelete:
            states_.insert_or_assign(state, std::make_shared<DeleteTaskState>(CreateStatesFactory()));
            break;
        case States::kSetLabel:
            states_.insert_or_assign(state, std::make_shared<SetLabelState>(CreateStatesFactory()));
            break;
        case States::kEnd:
            states_.insert_or_assign(state, std::make_shared<EndState>(CreateStatesFactory()));
            break;
        case States::kSave:
            states_.insert_or_assign(state, std::make_shared<SaveState>(CreateStatesFactory()));
            break;
        case States::kLoad:
            states_.insert_or_assign(state, std::make_shared<LoadState>(CreateStatesFactory()));
            break;
        case States::kShow:
            states_.insert_or_assign(state, std::make_shared<ShowState>(CreateStatesFactory()));
            break;
    }
}

std::unique_ptr<ConsoleStateMachine> StatesFactory::CreateStateMachine(const std::shared_ptr<State>& initial_state,
                                                                       const std::shared_ptr<StateContext>& context) const {
    return std::make_unique<ConsoleStateMachine>(initial_state, context);
}

std::shared_ptr<CommandFactory> StatesFactory::GetCommandFactory() const {
    return command_factory_;
}

std::shared_ptr<ConsolePrinter> StatesFactory::GetConsolePrinter() const {
    return printer_;
}

std::shared_ptr<ConsoleReader> StatesFactory::GetConsoleReader() const {
    return reader_;
}

std::shared_ptr<StatesFactory> StatesFactory::CreateStatesFactory() const {
    return std::make_shared<StatesFactory>(command_factory_, printer_, reader_);
}
