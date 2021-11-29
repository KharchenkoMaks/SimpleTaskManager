//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_WIZARDSTATESFACTORY_H
#define SIMPLETASKMANAGER_WIZARDSTATESFACTORY_H

#include "states/abstract/IWizardState.h"
#include "console_io/ConsolePrinter.h"
#include "console_io/ConsoleReader.h"

#include "states/RootState.h"
#include "states/HelpState.h"
#include "states/QuitState.h"
#include "states/task_input/AddTaskState.h"
#include "states/task_input/EditTaskState.h"
#include "states/task_input/InputTaskTitleState.h"
#include "states/task_input/InputTaskPriorityState.h"
#include "states/task_input/InputTaskDueDateState.h"

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

class WizardStatesFactory : public std::enable_shared_from_this<WizardStatesFactory> {
public:
    enum class MoveType{
        PREVIOUS,
        ERROR,
        NEXT
    };

public:
    std::shared_ptr<IWizardState> GetStateByCommand(const std::string& command);

    std::shared_ptr<IWizardState> GetInitialState();

    std::optional<std::shared_ptr<IWizardState>> GetNextState(const RootState& state, MoveType move_type);
    std::optional<std::shared_ptr<IWizardState>> GetNextState(const HelpState& state, MoveType move_type);
    std::optional<std::shared_ptr<IWizardState>> GetNextState(const QuitState& state, MoveType move_type);
    std::optional<std::shared_ptr<IWizardState>> GetNextState(const AddTaskState& state, MoveType move_type);
    std::optional<std::shared_ptr<IWizardState>> GetNextState(const EditTaskState& state, MoveType move_type);
    std::optional<std::shared_ptr<IWizardState>> GetNextState(const InputTaskTitleState& state, MoveType move_type);
    std::optional<std::shared_ptr<IWizardState>> GetNextState(const InputTaskPriorityState& state, MoveType move_type);
    std::optional<std::shared_ptr<IWizardState>> GetNextState(const InputTaskDueDateState& state, MoveType move_type);
private:
    enum class States {
        kRoot,
        kHelp,
        kQuit,
        kAddTask,
        kEditTask,
        kInputTaskTitle,
        kInputTaskPriority,
        kInputTaskDueDate
    };
private:
    std::shared_ptr<IWizardState> GetLazyStateByStatesEnum(States state);
private:
    std::shared_ptr<RootState> root_state_;
    std::shared_ptr<HelpState> help_state_;
    std::shared_ptr<QuitState> quit_state_;

    std::shared_ptr<AddTaskState> add_task_state_;
    std::shared_ptr<EditTaskState> edit_task_state_;

    std::shared_ptr<InputTaskTitleState> input_task_title_state_;
    std::shared_ptr<InputTaskPriorityState> input_task_priority_state_;
    std::shared_ptr<InputTaskDueDateState> input_task_due_date_state_;

    std::shared_ptr<ConsoleReader> reader_;
    std::shared_ptr<ConsolePrinter> printer_;
};


#endif //SIMPLETASKMANAGER_WIZARDSTATESFACTORY_H
