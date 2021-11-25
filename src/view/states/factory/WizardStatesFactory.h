//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_WIZARDSTATESFACTORY_H
#define SIMPLETASKMANAGER_WIZARDSTATESFACTORY_H

#include "states/abstract/IWizardState.h"
#include "ConsoleMultiFunctionalPrinter.h"

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
public:
    WizardStatesFactory();
    std::shared_ptr<IWizardState> GetStateByCommand(const std::string& command);

    std::shared_ptr<IWizardState> GetState(States state);
private:
    std::shared_ptr<RootState> root_state_;
    std::shared_ptr<HelpState> help_state_;
    std::shared_ptr<QuitState> quit_state_;

    std::shared_ptr<AddTaskState> add_task_state_;
    std::shared_ptr<EditTaskState> edit_task_state_;

    std::shared_ptr<InputTaskTitleState> input_task_title_state_;
    std::shared_ptr<InputTaskPriorityState> input_task_priority_state_;
    std::shared_ptr<InputTaskDueDateState> input_task_due_date_state_;

    std::shared_ptr<ConsoleMultiFunctionalPrinter> printer_;
};


#endif //SIMPLETASKMANAGER_WIZARDSTATESFACTORY_H
