//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "StatesFactory.h"
#include "ConsoleStateMachine.h"

#include "states/RootState.h"
#include "states/HelpState.h"
#include "states/QuitState.h"
#include "states/task_input/AddTaskState.h"
#include "states/task_input/EditTaskState.h"
#include "states/task_input/InputTaskTitleState.h"
#include "states/task_input/InputTaskPriorityState.h"
#include "states/task_input/InputTaskDueDateState.h"
#include "states/ShowState.h"
#include "states/CompleteTaskState.h"
#include "states/task_input/AddSubTaskState.h"
#include "states/DeleteTaskState.h"
#include "states/task_input/SetLabelState.h"
#include "states/EndState.h"
#include "states/persistence/SaveState.h"
#include "states/persistence/LoadState.h"

StatesFactory::StatesFactory(const std::shared_ptr<Controller>& controller,
                                         const std::shared_ptr<ConsolePrinter>& printer,
                                         const std::shared_ptr<ConsoleReader>& reader) :
                                         controller_(controller),
                                         printer_(printer),
                                         reader_(reader) {

}

std::shared_ptr<StateInterface> StatesFactory::GetStateByCommand(const std::string &command) {
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
        return GetLazyStateByStatesEnum(States::kShow);
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

std::shared_ptr<StateInterface> StatesFactory::GetInitialState() {
    return GetLazyStateByStatesEnum(States::kRoot);
}

std::shared_ptr<StateInterface> StatesFactory::GetNextState(const QuitState& state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::PREVIOUS: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
        case MoveType::ERROR: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
        case MoveType::NEXT: {
            return GetLazyStateByStatesEnum(States::kEnd);
        }
    }
}

std::shared_ptr<StateInterface> StatesFactory::GetNextState(const AddTaskState &state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::PREVIOUS: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
        case MoveType::ERROR: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
        case MoveType::NEXT: {
            return GetLazyStateByStatesEnum(States::kInputTaskTitle);
        }
    }
}

std::shared_ptr<StateInterface> StatesFactory::GetNextState(const AddSubTaskState& state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::PREVIOUS: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
        case MoveType::ERROR: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
        case MoveType::NEXT: {
            return GetLazyStateByStatesEnum(States::kInputTaskTitle);
        }
    }
}

std::shared_ptr<StateInterface> StatesFactory::GetNextState(const EditTaskState &state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::PREVIOUS: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
        case MoveType::ERROR: {
            return GetLazyStateByStatesEnum(States::kEditTask);
        }
        case MoveType::NEXT: {
            return GetLazyStateByStatesEnum(States::kInputTaskTitle);
        }
    }
}

std::shared_ptr<StateInterface> StatesFactory::GetNextState(const InputTaskTitleState &state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::NEXT: {
            return GetLazyStateByStatesEnum(States::kInputTaskPriority);
        }
        default: {
            return GetLazyStateByStatesEnum(States::kInputTaskTitle);
        }
    };
}

std::shared_ptr<StateInterface> StatesFactory::GetNextState(const InputTaskPriorityState &state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::PREVIOUS: {
            return GetLazyStateByStatesEnum(States::kInputTaskTitle);
        }
        case MoveType::ERROR: {
            return GetLazyStateByStatesEnum(States::kInputTaskPriority);
        }
        case MoveType::NEXT: {
            return GetLazyStateByStatesEnum(States::kInputTaskDueDate);
        }
    }
}

std::shared_ptr<StateInterface> StatesFactory::GetNextState(const InputTaskDueDateState &state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::PREVIOUS: {
            return GetLazyStateByStatesEnum(States::kInputTaskPriority);
        }
        case MoveType::ERROR: {
            return GetLazyStateByStatesEnum(States::kInputTaskDueDate);
        }
        case MoveType::NEXT: {
            return GetLazyStateByStatesEnum(States::kEnd);
        }
    }
}

std::shared_ptr<StateInterface> StatesFactory::GetNextState(const HelpState &state, MoveType move_type) {
    switch (move_type) {
        default: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
    }
}

std::shared_ptr<StateInterface> StatesFactory::GetNextState(const RootState &state, StatesFactory::MoveType move_type) {
    switch (move_type) {
        default: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
    }
}

std::shared_ptr<StateInterface> StatesFactory::GetNextState(const ShowState &state, StatesFactory::MoveType move_type) {
    switch (move_type) {
        default: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
    }
}

std::shared_ptr<StateInterface> StatesFactory::GetNextState(const CompleteTaskState &state, StatesFactory::MoveType move_type) {
    switch (move_type) {
        case MoveType::ERROR: {
            return GetLazyStateByStatesEnum(States::kComplete);
        }
        default: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
    }
}

std::shared_ptr<StateInterface> StatesFactory::GetNextState(const DeleteTaskState& state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::ERROR: {
            return GetLazyStateByStatesEnum(States::kDelete);
        }
        default: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
    }
}

std::shared_ptr<StateInterface> StatesFactory::GetNextState(const SetLabelState &state, const StatesFactory::MoveType move_type) {
    switch (move_type) {
        case MoveType::ERROR: {
            return GetLazyStateByStatesEnum(States::kSetLabel);
        }
        default: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
    }
}

std::shared_ptr<StateInterface> StatesFactory::GetNextState(const SaveState &state, const StatesFactory::MoveType move_type) {
    switch(move_type) {
        case MoveType::ERROR: {
            return GetLazyStateByStatesEnum(States::kSave);
        }
        default: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
    }
}

std::shared_ptr<StateInterface> StatesFactory::GetNextState(const LoadState &state, const StatesFactory::MoveType move_type) {
    switch(move_type) {
        case MoveType::ERROR: {
            return GetLazyStateByStatesEnum(States::kSave);
        }
        default: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
    }
}

std::shared_ptr<StateInterface> StatesFactory::GetLazyStateByStatesEnum(StatesFactory::States state) {
    auto found_state = states_.find(state);
    if (found_state == states_.end()) {
        InitializeState(state);
        found_state = states_.find(state);
    }
    return found_state->second;
}

void StatesFactory::InitializeState(States state) {
    switch (state) {
        case States::kRoot: {
            states_.insert_or_assign(state, std::make_shared<RootState>(shared_from_this()));
            break;
        }
        case States::kHelp: {
            states_.insert_or_assign(state, std::make_shared<HelpState>(shared_from_this()));
            break;
        }
        case States::kQuit: {
            states_.insert_or_assign(state, std::make_shared<QuitState>(shared_from_this()));
            break;
        }
        case States::kAddTask: {
            states_.insert_or_assign(state, std::make_shared<AddTaskState>(shared_from_this()));
            break;
        }
        case States::kAddSubTask: {
            states_.insert_or_assign(state, std::make_shared<AddSubTaskState>(shared_from_this()));
            break;
        }
        case States::kEditTask: {
            states_.insert_or_assign(state, std::make_shared<EditTaskState>(shared_from_this()));
            break;
        }
        case States::kInputTaskTitle: {
            states_.insert_or_assign(state, std::make_shared<InputTaskTitleState>(shared_from_this()));
            break;
        }
        case States::kInputTaskPriority: {
            states_.insert_or_assign(state, std::make_shared<InputTaskPriorityState>(shared_from_this()));
            break;
        }
        case States::kInputTaskDueDate: {
            states_.insert_or_assign(state, std::make_shared<InputTaskDueDateState>(shared_from_this()));
            break;
        }
        case States::kShow: {
            states_.insert_or_assign(state, std::make_shared<ShowState>(shared_from_this()));
            break;
        }
        case States::kComplete: {
            states_.insert_or_assign(state, std::make_shared<CompleteTaskState>(shared_from_this()));
            break;
        }
        case States::kDelete: {
            states_.insert_or_assign(state, std::make_shared<DeleteTaskState>(shared_from_this()));
            break;
        }
        case States::kSetLabel: {
            states_.insert_or_assign(state, std::make_shared<SetLabelState>(shared_from_this()));
            break;
        }
        case States::kEnd: {
            states_.insert_or_assign(state, std::make_shared<EndState>(shared_from_this()));
            break;
        }
        case States::kSave: {
            states_.insert_or_assign(state, std::make_shared<SaveState>(shared_from_this()));
            break;
        }
        case States::kLoad: {
            states_.insert_or_assign(state, std::make_shared<LoadState>(shared_from_this()));
            break;
        }
    }
}

std::shared_ptr<ConsolePrinter> StatesFactory::GetConsolePrinter() const {
    return printer_;
}

std::shared_ptr<ConsoleReader> StatesFactory::GetConsoleReader() const {
    return reader_;
}

std::shared_ptr<Controller> StatesFactory::GetController() const {
    return controller_;
}

std::unique_ptr<ConsoleStateMachine> StatesFactory::CreateStateMachine() const {
    return std::make_unique<ConsoleStateMachine>();
}
