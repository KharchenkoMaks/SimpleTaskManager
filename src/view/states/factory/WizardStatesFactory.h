//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_WIZARDSTATESFACTORY_H
#define SIMPLETASKMANAGER_WIZARDSTATESFACTORY_H

#include "states/abstract/WizardStateInterface.h"
#include "console_io/ConsolePrinter.h"
#include "console_io/ConsoleReader.h"
#include "Controller.h"
#include "states/abstract/StateDependencies.h"

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
class SetLabelState;
class EndState;
class SaveState;
class LoadState;

class WizardStatesFactory : public std::enable_shared_from_this<WizardStatesFactory> {
public:
    enum class MoveType{
        PREVIOUS,
        ERROR,
        NEXT
    };

public:
    WizardStatesFactory(const std::shared_ptr<Controller>& controller,
                        const std::shared_ptr<ConsolePrinter>& printer,
                        const std::shared_ptr<ConsoleReader>& reader);

public:
    virtual std::shared_ptr<WizardStateInterface> GetStateByCommand(const std::string& command);

    std::shared_ptr<WizardStateInterface> GetInitialState();

    virtual std::shared_ptr<WizardStateInterface> GetNextState(const RootState& state, MoveType move_type);
    virtual std::shared_ptr<WizardStateInterface> GetNextState(const HelpState& state, MoveType move_type);
    virtual std::shared_ptr<WizardStateInterface> GetNextState(const QuitState& state, MoveType move_type);
    virtual std::shared_ptr<WizardStateInterface> GetNextState(const AddTaskState& state, MoveType move_type);
    virtual std::shared_ptr<WizardStateInterface> GetNextState(const EditTaskState& state, MoveType move_type);
    virtual std::shared_ptr<WizardStateInterface> GetNextState(const InputTaskTitleState& state, MoveType move_type);
    virtual std::shared_ptr<WizardStateInterface> GetNextState(const InputTaskPriorityState& state, MoveType move_type);
    virtual std::shared_ptr<WizardStateInterface> GetNextState(const InputTaskDueDateState& state, MoveType move_type);
    virtual std::shared_ptr<WizardStateInterface> GetNextState(const ShowState& state, MoveType move_type);
    virtual std::shared_ptr<WizardStateInterface> GetNextState(const CompleteTaskState& state, MoveType move_type);
    virtual std::shared_ptr<WizardStateInterface> GetNextState(const AddSubTaskState& state, MoveType move_type);
    virtual std::shared_ptr<WizardStateInterface> GetNextState(const DeleteTaskState& state, MoveType move_type);
    virtual std::shared_ptr<WizardStateInterface> GetNextState(const SetLabelState& state, MoveType move_type);
    virtual std::shared_ptr<WizardStateInterface> GetNextState(const SaveState& state, MoveType move_type);
    virtual std::shared_ptr<WizardStateInterface> GetNextState(const LoadState& state, MoveType move_type);

public:
    virtual ~WizardStatesFactory() = default;

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
        kDelete,
        kSetLabel,
        kEnd,
        kSave,
        kLoad
    };
private:
    std::shared_ptr<WizardStateInterface> GetLazyStateByStatesEnum(States state);
    void InitializeState(States state);

private:
    std::map<States, std::shared_ptr<WizardStateInterface>> states_;

    std::shared_ptr<ConsoleReader> reader_;
    std::shared_ptr<ConsolePrinter> printer_;

    std::shared_ptr<Controller> controller_;
};


#endif //SIMPLETASKMANAGER_WIZARDSTATESFACTORY_H
