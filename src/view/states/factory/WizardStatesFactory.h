//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_WIZARDSTATESFACTORY_H
#define SIMPLETASKMANAGER_WIZARDSTATESFACTORY_H

#include "states/abstract/WizardStateConsole.h"
#include "console_io/ConsolePrinter.h"
#include "console_io/ConsoleReader.h"
#include "Controller.h"

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

#include <memory>
#include <string>
#include <optional>

class RootState;
class HelpState;
class QuitState;
class AddTaskState;
class EditTaskState;
class InputTaskTitleState;
class InputTaskPriorityState;
class InputTaskDueDateState;
class ShowState;
class CompleteTaskState;
class AddSubTaskState;
class DeleteTaskState;

class WizardStatesFactory : public std::enable_shared_from_this<WizardStatesFactory> {
public:
    enum class MoveType{
        PREVIOUS,
        ERROR,
        NEXT
    };

public:
    explicit WizardStatesFactory(const std::shared_ptr<Controller>& controller);

public:
    std::optional<std::shared_ptr<WizardStateConsole>> GetStateByCommand(const std::string& command);

    std::shared_ptr<WizardStateConsole> GetInitialState();

    std::optional<std::shared_ptr<WizardStateConsole>> GetNextState(const RootState& state, MoveType move_type);
    std::optional<std::shared_ptr<WizardStateConsole>> GetNextState(const HelpState& state, MoveType move_type);
    std::optional<std::shared_ptr<WizardStateConsole>> GetNextState(const QuitState& state, MoveType move_type);
    std::optional<std::shared_ptr<WizardStateConsole>> GetNextState(const AddTaskState& state, MoveType move_type);
    std::optional<std::shared_ptr<WizardStateConsole>> GetNextState(const EditTaskState& state, MoveType move_type);
    std::optional<std::shared_ptr<WizardStateConsole>> GetNextState(const InputTaskTitleState& state, MoveType move_type);
    std::optional<std::shared_ptr<WizardStateConsole>> GetNextState(const InputTaskPriorityState& state, MoveType move_type);
    std::optional<std::shared_ptr<WizardStateConsole>> GetNextState(const InputTaskDueDateState& state, MoveType move_type);
    std::optional<std::shared_ptr<WizardStateConsole>> GetNextState(const ShowState& state, MoveType move_type);
    std::optional<std::shared_ptr<WizardStateConsole>> GetNextState(const CompleteTaskState& state, MoveType move_type);
    std::optional<std::shared_ptr<WizardStateConsole>> GetNextState(const AddSubTaskState& state, MoveType move_type);
    std::optional<std::shared_ptr<WizardStateConsole>> GetNextState(const DeleteTaskState& state, MoveType move_type);

private:
    enum class States {
        kRoot,
        kHelp,
        kQuit,
        kAddTask,
        kAddSubTask,
        kEditTask,
        kInputTaskTitle,
        kInputTaskPriority,
        kInputTaskDueDate,
        kShow,
        kComplete,
        kDelete
    };
private:
    std::shared_ptr<WizardStateConsole> GetLazyStateByStatesEnum(States state);

private:
    std::shared_ptr<RootState> root_state_;
    std::shared_ptr<HelpState> help_state_;
    std::shared_ptr<QuitState> quit_state_;

    std::shared_ptr<AddTaskState> add_task_state_;
    std::shared_ptr<AddSubTaskState> add_subtask_state_;
    std::shared_ptr<EditTaskState> edit_task_state_;

    std::shared_ptr<ShowState> show_state_;
    std::shared_ptr<CompleteTaskState> complete_state_;
    std::shared_ptr<DeleteTaskState> delete_state_;

    std::shared_ptr<InputTaskTitleState> input_task_title_state_;
    std::shared_ptr<InputTaskPriorityState> input_task_priority_state_;
    std::shared_ptr<InputTaskDueDateState> input_task_due_date_state_;

    std::shared_ptr<ConsoleReader> reader_;
    std::shared_ptr<ConsolePrinter> printer_;

    std::shared_ptr<Controller> controller_;
};


#endif //SIMPLETASKMANAGER_WIZARDSTATESFACTORY_H
