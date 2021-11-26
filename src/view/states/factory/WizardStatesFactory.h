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

class WizardStatesFactory {
public:
    WizardStatesFactory();

public:
    std::shared_ptr<IWizardState> GetStateByCommand(const std::string& command);

    std::shared_ptr<IWizardState> GetInitialState();

    std::optional<std::shared_ptr<IWizardState>> GetPreviousState(const RootState& state);
    std::optional<std::shared_ptr<IWizardState>> GetPreviousState(const HelpState& state);
    std::optional<std::shared_ptr<IWizardState>> GetPreviousState(const QuitState& state);
    std::optional<std::shared_ptr<IWizardState>> GetPreviousState(const AddTaskState& state);
    std::optional<std::shared_ptr<IWizardState>> GetPreviousState(const EditTaskState& state);
    std::optional<std::shared_ptr<IWizardState>> GetPreviousState(const InputTaskTitleState& state);
    std::optional<std::shared_ptr<IWizardState>> GetPreviousState(const InputTaskPriorityState& state);
    std::optional<std::shared_ptr<IWizardState>> GetPreviousState(const InputTaskDueDateState& state);

    std::optional<std::shared_ptr<IWizardState>> GetNextState(const QuitState& state);
    std::optional<std::shared_ptr<IWizardState>> GetNextState(const AddTaskState& state);
    std::optional<std::shared_ptr<IWizardState>> GetNextState(const EditTaskState& state);
    std::optional<std::shared_ptr<IWizardState>> GetNextState(const InputTaskTitleState& state);
    std::optional<std::shared_ptr<IWizardState>> GetNextState(const InputTaskPriorityState& state);
    std::optional<std::shared_ptr<IWizardState>> GetNextState(const InputTaskDueDateState& state);
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
