//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_WIZARDSTATESFACTORY_H
#define SIMPLETASKMANAGER_WIZARDSTATESFACTORY_H

#include "states/abstract/IWizardState.h"
#include "printer/ConsolePrinter.h"

#include "states/RootState.h"
#include "states/HelpState.h"
#include "states/quit/QuitState.h"
#include "states/confirm/ConfirmState.h"
#include "states/add_task/AddTaskState.h"
#include "states/edit_task/EditTaskState.h"
#include "states/task_input/InputTaskTitleState.h"
#include "states/task_input/InputTaskPriorityState.h"
#include "states/task_input/InputTaskDueDateState.h"

#include <memory>
#include <string>

class RootState;
class HelpState;
class QuitState;
class ConfirmState;
class AddTaskState;
class EditTaskState;
class InputTaskTitleState;
class InputTaskPriorityState;
class InputTaskDueDateState;

class WizardStatesFactory {
public:
    enum class States {
        kRoot,
        kHelp,
        kQuit,
        kConfirm,
        kAddTask,
        kEditTask,
        kInputTaskTitle,
        kInputTaskPriority,
        kInputTaskDueDate
    };
public:
    WizardStatesFactory();
    std::shared_ptr<IWizardState> GetStateByCommand(const std::string& command);

    std::shared_ptr<IWizardState> GetState(States state);
private:
    std::shared_ptr<RootState> root_state_;
    std::shared_ptr<HelpState> help_state_;
    std::shared_ptr<QuitState> quit_state_;
    std::shared_ptr<ConfirmState> confirm_state_;

    std::shared_ptr<AddTaskState> add_task_state_;
    std::shared_ptr<EditTaskState> edit_task_state_;

    std::shared_ptr<InputTaskTitleState> input_task_title_state_;
    std::shared_ptr<InputTaskPriorityState> input_task_priority_state_;
    std::shared_ptr<InputTaskDueDateState> input_task_due_date_state_;

    std::shared_ptr<ConsolePrinter> printer_;
};


#endif //SIMPLETASKMANAGER_WIZARDSTATESFACTORY_H
