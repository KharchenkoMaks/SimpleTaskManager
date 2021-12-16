//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "WizardStatesFactory.h"
#include "ConsoleStateMachine.h"

WizardStatesFactory::WizardStatesFactory(const std::shared_ptr<Controller>& controller,
                                         const std::shared_ptr<ConsolePrinter>& printer,
                                         const std::shared_ptr<ConsoleReader>& reader) :
                                         controller_(controller),
                                         printer_(printer),
                                         reader_(reader) {

}

std::shared_ptr<WizardStateInterface> WizardStatesFactory::GetStateByCommand(const std::string &command) {
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
    } else if (command == "set_label") {
        return GetLazyStateByStatesEnum(States::kSetLabel);
    } else if (command == "save") {
        return GetLazyStateByStatesEnum(States::kSave);
    } else if (command == "load") {
        return GetLazyStateByStatesEnum(States::kLoad);
    } else {
        return nullptr;
    }
}

std::shared_ptr<WizardStateInterface> WizardStatesFactory::GetInitialState() {
    return GetLazyStateByStatesEnum(States::kRoot);
}

std::shared_ptr<WizardStateInterface> WizardStatesFactory::GetNextState(const QuitState& state, const MoveType move_type) {
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

std::shared_ptr<WizardStateInterface> WizardStatesFactory::GetNextState(const AddTaskState &state, const MoveType move_type) {
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

std::shared_ptr<WizardStateInterface> WizardStatesFactory::GetNextState(const AddSubTaskState& state, const MoveType move_type) {
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

std::shared_ptr<WizardStateInterface> WizardStatesFactory::GetNextState(const EditTaskState &state, const MoveType move_type) {
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

std::shared_ptr<WizardStateInterface> WizardStatesFactory::GetNextState(const InputTaskTitleState &state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::NEXT: {
            return GetLazyStateByStatesEnum(States::kInputTaskPriority);
        }
        default: {
            return GetLazyStateByStatesEnum(States::kInputTaskTitle);
        }
    };
}

std::shared_ptr<WizardStateInterface> WizardStatesFactory::GetNextState(const InputTaskPriorityState &state, const MoveType move_type) {
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

std::shared_ptr<WizardStateInterface> WizardStatesFactory::GetNextState(const InputTaskDueDateState &state, const MoveType move_type) {
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

std::shared_ptr<WizardStateInterface> WizardStatesFactory::GetNextState(const HelpState &state, MoveType move_type) {
    switch (move_type) {
        default: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
    }
}

std::shared_ptr<WizardStateInterface> WizardStatesFactory::GetNextState(const RootState &state, WizardStatesFactory::MoveType move_type) {
    switch (move_type) {
        default: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
    }
}

std::shared_ptr<WizardStateInterface> WizardStatesFactory::GetNextState(const ShowState &state, WizardStatesFactory::MoveType move_type) {
    switch (move_type) {
        default: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
    }
}

std::shared_ptr<WizardStateInterface> WizardStatesFactory::GetNextState(const CompleteTaskState &state, WizardStatesFactory::MoveType move_type) {
    switch (move_type) {
        case MoveType::ERROR: {
            return GetLazyStateByStatesEnum(States::kComplete);
        }
        default: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
    }
}

std::shared_ptr<WizardStateInterface> WizardStatesFactory::GetNextState(const DeleteTaskState& state, const MoveType move_type) {
    switch (move_type) {
        case MoveType::ERROR: {
            return GetLazyStateByStatesEnum(States::kDelete);
        }
        default: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
    }
}

std::shared_ptr<WizardStateInterface> WizardStatesFactory::GetNextState(const SetLabelState &state, const WizardStatesFactory::MoveType move_type) {
    switch (move_type) {
        case MoveType::ERROR: {
            return GetLazyStateByStatesEnum(States::kSetLabel);
        }
        default: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
    }
}

std::shared_ptr<WizardStateInterface> WizardStatesFactory::GetNextState(const SaveState &state, const WizardStatesFactory::MoveType move_type) {
    switch(move_type) {
        case MoveType::ERROR: {
            return GetLazyStateByStatesEnum(States::kSave);
        }
        default: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
    }
}

std::shared_ptr<WizardStateInterface> WizardStatesFactory::GetNextState(const LoadState &state, const WizardStatesFactory::MoveType move_type) {
    switch(move_type) {
        case MoveType::ERROR: {
            return GetLazyStateByStatesEnum(States::kSave);
        }
        default: {
            return GetLazyStateByStatesEnum(States::kRoot);
        }
    }
}

std::shared_ptr<WizardStateInterface> WizardStatesFactory::GetLazyStateByStatesEnum(States state) {
    switch (state) {
        case States::kRoot: {
            if (!root_state_){
                root_state_ = std::make_shared<RootState>(
                        std::make_unique<StateDependencies>(std::make_unique<ConsoleStateMachine>(),
                                                                        shared_from_this(),
                                                                        controller_,
                                                                        printer_,
                                                                        reader_));
            }
            return root_state_;
        }
        case States::kHelp: {
            if (!help_state_){
                help_state_ = std::make_shared<HelpState>(
                        std::make_unique<StateDependencies>(std::make_unique<ConsoleStateMachine>(),
                                                            shared_from_this(),
                                                            controller_,
                                                            printer_,
                                                            reader_));
            }
            return help_state_;
        }
        case States::kQuit: {
            if (!quit_state_){
                quit_state_ = std::make_shared<QuitState>(
                        std::make_unique<StateDependencies>(std::make_unique<ConsoleStateMachine>(),
                                                            shared_from_this(),
                                                            controller_,
                                                            printer_,
                                                            reader_));
            }
            return quit_state_;
        }
        case States::kAddTask: {
            if (!add_task_state_) {
                add_task_state_ = std::make_shared<AddTaskState>(
                        std::make_unique<StateDependencies>(std::make_unique<ConsoleStateMachine>(),
                                                            shared_from_this(),
                                                            controller_,
                                                            printer_,
                                                            reader_));
            }
            return add_task_state_;
        }
        case States::kAddSubTask: {
            if (!add_subtask_state_) {
                add_subtask_state_ = std::make_shared<AddSubTaskState>(
                        std::make_unique<StateDependencies>(std::make_unique<ConsoleStateMachine>(),
                                                            shared_from_this(),
                                                            controller_,
                                                            printer_,
                                                            reader_));
            }
            return add_subtask_state_;
        }
        case States::kEditTask: {
            if (!edit_task_state_){
                edit_task_state_ = std::make_shared<EditTaskState>(
                        std::make_unique<StateDependencies>(std::make_unique<ConsoleStateMachine>(),
                                                            shared_from_this(),
                                                            controller_,
                                                            printer_,
                                                            reader_));
            }
            return edit_task_state_;
        }
        case States::kInputTaskTitle: {
            if (!input_task_title_state_){
                input_task_title_state_ = std::make_shared<InputTaskTitleState>(
                        std::make_unique<StateDependencies>(std::make_unique<ConsoleStateMachine>(),
                                                            shared_from_this(),
                                                            controller_,
                                                            printer_,
                                                            reader_));
            }
            return input_task_title_state_;
        }
        case States::kInputTaskPriority: {
            if (!input_task_priority_state_){
                input_task_priority_state_ = std::make_shared<InputTaskPriorityState>(
                        std::make_unique<StateDependencies>(std::make_unique<ConsoleStateMachine>(),
                                                            shared_from_this(),
                                                            controller_,
                                                            printer_,
                                                            reader_));
            }
            return input_task_priority_state_;
        }
        case States::kInputTaskDueDate: {
            if (!input_task_due_date_state_){
                input_task_due_date_state_ = std::make_shared<InputTaskDueDateState>(
                        std::make_unique<StateDependencies>(std::make_unique<ConsoleStateMachine>(),
                                                            shared_from_this(),
                                                            controller_,
                                                            printer_,
                                                            reader_));
            }
            return input_task_due_date_state_;
        }
        case States::kShow: {
            if (!show_state_) {
                show_state_ = std::make_shared<ShowState>(
                        std::make_unique<StateDependencies>(
                                std::make_unique<ConsoleStateMachine>(),
                                                            shared_from_this(),
                                                            controller_,
                                                            printer_,
                                                            reader_));
            }
            return show_state_;
        }
        case States::kComplete: {
            if (!complete_state_) {
                complete_state_ = std::make_shared<CompleteTaskState>(
                        std::make_unique<StateDependencies>(std::make_unique<ConsoleStateMachine>(),
                                                            shared_from_this(),
                                                            controller_,
                                                            printer_,
                                                            reader_));
            }
            return complete_state_;
        }
        case States::kDelete: {
            if (!delete_state_) {
                delete_state_ = std::make_shared<DeleteTaskState>(
                        std::make_unique<StateDependencies>(std::make_unique<ConsoleStateMachine>(),
                                                            shared_from_this(),
                                                            controller_,
                                                            printer_,
                                                            reader_));
            }
            return delete_state_;
        }
        case States::kSetLabel: {
            if (!set_label_state_) {
                set_label_state_ = std::make_shared<SetLabelState>(
                        std::make_unique<StateDependencies>(std::make_unique<ConsoleStateMachine>(),
                                                            shared_from_this(),
                                                            controller_,
                                                            printer_,
                                                            reader_));
            }
            return set_label_state_;
        }
        case States::kEnd: {
            if (!end_state_) {
                end_state_ = std::make_shared<EndState>(
                        std::make_unique<StateDependencies>(std::make_unique<ConsoleStateMachine>(),
                                                            shared_from_this(),
                                                            controller_,
                                                            printer_,
                                                            reader_));
            }
            return end_state_;
        }
        case States::kSave: {
            if (!save_state_) {
                save_state_ = std::make_shared<SaveState>(
                        std::make_unique<StateDependencies>(std::make_unique<ConsoleStateMachine>(),
                                                            shared_from_this(),
                                                            controller_,
                                                            printer_,
                                                            reader_));
            }
            return save_state_;
        }
        case States::kLoad: {
            if (!load_state_) {
                load_state_ = std::make_shared<LoadState>(
                        std::make_unique<StateDependencies>(std::make_unique<ConsoleStateMachine>(),
                                                            shared_from_this(),
                                                            controller_,
                                                            printer_,
                                                            reader_));
            }
            return load_state_;
        }
    }
}
