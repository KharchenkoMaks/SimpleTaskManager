//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "LazyStatesFactory.h"

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
#include "states/task_input/RemoveLabelState.h"
#include "states/persistence/SaveState.h"
#include "states/persistence/LoadState.h"
#include "states/ShowState.h"

#include "user_interface/ConsoleStateMachine.h"

LazyStatesFactory::LazyStatesFactory(const std::shared_ptr<CommandFactory>& command_factory,
                                     const std::shared_ptr<ConsolePrinter>& printer,
                                     const std::shared_ptr<ConsoleReader>& reader) :
                                     command_factory_(command_factory),
                                     printer_(printer),
                                     reader_(reader) {}

std::shared_ptr<State> LazyStatesFactory::GetState(StateType state) {
    if (state == StateType::kEnd)
        return nullptr;

    auto found_state = states_.find(state);
    if (found_state == states_.end()) {
        InitializeState(state);
        found_state = states_.find(state);
    }
    return found_state->second;
}

void LazyStatesFactory::InitializeState(StateType state) {
    switch (state) {
        case StateType::kRoot:
            states_.insert_or_assign(state, std::make_shared<RootState>(StateType::kRoot, printer_, reader_));
            break;
        case StateType::kHelp:
            states_.insert_or_assign(state, std::make_shared<HelpState>(StateType::kRoot, printer_));
            break;
        case StateType::kQuit:
            states_.insert_or_assign(state, std::make_shared<QuitState>(StateType::kEnd, StateType::kRoot, printer_, reader_));
            break;
        case StateType::kAddTask:
            states_.insert_or_assign(state, std::make_shared<AddTaskState>(StateType::kEnd, command_factory_,
                                                                           CreateStateMachine(StateType::kInputTaskTitle, std::make_unique<StateContext>())));
            break;
        case StateType::kAddSubTask:
            states_.insert_or_assign(state, std::make_shared<AddSubTaskState>(StateType::kEnd, StateType::kAddSubTask, printer_, reader_, command_factory_,
                                                                              CreateStateMachine(StateType::kInputTaskTitle, std::make_unique<StateContext>())));
            break;
        case StateType::kEditTask:
            states_.insert_or_assign(state, std::make_shared<EditTaskState>(StateType::kEnd, StateType::kEditTask, printer_, reader_, command_factory_,
                                                                            CreateStateMachine(StateType::kInputTaskTitle, std::make_unique<StateContext>())));
            break;
        case StateType::kInputTaskTitle:
            states_.insert_or_assign(state, std::make_shared<InputTaskTitleState>(StateType::kInputTaskPriority, printer_, reader_));
            break;
        case StateType::kInputTaskPriority:
            states_.insert_or_assign(state, std::make_shared<InputTaskPriorityState>(StateType::kInputTaskDueDate, StateType::kInputTaskPriority, printer_, reader_));
            break;
        case StateType::kInputTaskDueDate:
            states_.insert_or_assign(state, std::make_shared<InputTaskDueDateState>(StateType::kEnd, StateType::kInputTaskDueDate, printer_, reader_));
            break;
        case StateType::kInputShowParameters:
            states_.insert_or_assign(state, std::make_shared<InputShowParametersState>(StateType::kEnd, command_factory_,
                                                                                       CreateStateMachine(StateType::kInputShowTaskLabel, std::make_unique<StateContext>())));
            break;
        case StateType::kInputShowTaskLabel:
            states_.insert_or_assign(state, std::make_shared<InputShowByLabelState>(StateType::kEnd, printer_, reader_));
            break;
        case StateType::kComplete:
            states_.insert_or_assign(state, std::make_shared<CompleteTaskState>(StateType::kEnd, StateType::kComplete, printer_, reader_, command_factory_));
            break;
        case StateType::kDelete:
            states_.insert_or_assign(state, std::make_shared<DeleteTaskState>(StateType::kEnd, StateType::kDelete, printer_, reader_, command_factory_));
            break;
        case StateType::kAddLabel:
            states_.insert_or_assign(state, std::make_shared<SetLabelState>(StateType::kEnd, StateType::kAddLabel, printer_, reader_, command_factory_));
            break;
        case StateType::kRemoveLabel:
            states_.insert_or_assign(state, std::make_shared<RemoveLabelState>(StateType::kEnd, StateType::kRemoveLabel, printer_, reader_, command_factory_));
            break;
        case StateType::kEnd:
            // can't generate this state
            break;
        case StateType::kSave:
            states_.insert_or_assign(state, std::make_shared<SaveState>(StateType::kEnd, StateType::kSave, printer_, reader_, command_factory_));
            break;
        case StateType::kLoad:
            states_.insert_or_assign(state, std::make_shared<LoadState>(StateType::kEnd, StateType::kLoad, printer_, reader_, command_factory_));
            break;
        case StateType::kShow:
            states_.insert_or_assign(state, std::make_shared<ShowState>(StateType::kEnd, printer_));
            break;
    }
}

std::unique_ptr<ConsoleStateMachine> LazyStatesFactory::CreateStateMachine(const StateType initial_state,
                                                                           std::unique_ptr<StateContext> context) {
    return CreateStateMachine(initial_state, std::move(context), std::make_shared<LazyStatesFactory>(command_factory_, printer_, reader_));
}

std::unique_ptr<ConsoleStateMachine> LazyStatesFactory::CreateStateMachine(const StateType initial_state,
                                                                           std::unique_ptr<StateContext> context,
                                                                           const std::shared_ptr<StatesFactory>& states_factory) {
    return std::make_unique<ConsoleStateMachine>(initial_state, std::move(context), states_factory);
}
