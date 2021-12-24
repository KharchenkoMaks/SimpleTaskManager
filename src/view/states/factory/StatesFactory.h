//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_STATESFACTORY_H
#define SIMPLETASKMANAGER_STATESFACTORY_H

#include "states/StateInterface.h"
#include "user_interface/console_io/ConsolePrinter.h"
#include "user_interface/console_io/ConsoleReader.h"
#include "Controller.h"
#include "user_interface/ConsoleStateMachine.h"
#include "commands/factory/CommandFactory.h"

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
class InputShowParametersState;
class CompleteTaskState;
class AddSubTaskState;
class DeleteTaskState;
class SetLabelState;
class EndState;
class SaveState;
class LoadState;
class ShowState;

class StatesFactory : public std::enable_shared_from_this<StatesFactory> {
public:
    enum class MoveType{
        PREVIOUS,
        ERROR,
        NEXT
    };

public:
    StatesFactory(const std::shared_ptr<CommandFactory>& command_factory,
                  const std::shared_ptr<ConsolePrinter>& printer,
                  const std::shared_ptr<ConsoleReader>& reader);

public:
    std::shared_ptr<ConsolePrinter> GetConsolePrinter() const;
    std::shared_ptr<ConsoleReader> GetConsoleReader() const;
    std::shared_ptr<CommandFactory> GetCommandFactory() const;

public:
    std::unique_ptr<ConsoleStateMachine> CreateStateMachine() const;

public:
    virtual std::shared_ptr<StateInterface> GetStateByCommand(const std::string& command);

    std::shared_ptr<StateInterface> GetRootState();
    std::shared_ptr<StateInterface> GetShowState();

    virtual std::shared_ptr<StateInterface> GetNextState(const RootState& state, MoveType move_type);
    virtual std::shared_ptr<StateInterface> GetNextState(const HelpState& state, MoveType move_type);
    virtual std::shared_ptr<StateInterface> GetNextState(const QuitState& state, MoveType move_type);
    virtual std::shared_ptr<StateInterface> GetNextState(const AddTaskState& state, MoveType move_type);
    virtual std::shared_ptr<StateInterface> GetNextState(const EditTaskState& state, MoveType move_type);
    virtual std::shared_ptr<StateInterface> GetNextState(const InputTaskTitleState& state, MoveType move_type);
    virtual std::shared_ptr<StateInterface> GetNextState(const InputTaskPriorityState& state, MoveType move_type);
    virtual std::shared_ptr<StateInterface> GetNextState(const InputTaskDueDateState& state, MoveType move_type);
    virtual std::shared_ptr<StateInterface> GetNextState(const InputShowParametersState& state, MoveType move_type);
    virtual std::shared_ptr<StateInterface> GetNextState(const CompleteTaskState& state, MoveType move_type);
    virtual std::shared_ptr<StateInterface> GetNextState(const AddSubTaskState& state, MoveType move_type);
    virtual std::shared_ptr<StateInterface> GetNextState(const DeleteTaskState& state, MoveType move_type);
    virtual std::shared_ptr<StateInterface> GetNextState(const SetLabelState& state, MoveType move_type);
    virtual std::shared_ptr<StateInterface> GetNextState(const SaveState& state, MoveType move_type);
    virtual std::shared_ptr<StateInterface> GetNextState(const LoadState& state, MoveType move_type);
    virtual std::shared_ptr<StateInterface> GetNextState(const ShowState& state, MoveType move_type);

public:
    virtual ~StatesFactory() = default;

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
        kInputShowParameters,
        kComplete,
        kDelete,
        kSetLabel,
        kEnd,
        kSave,
        kLoad,
        kShow
    };
private:
    std::shared_ptr<StateInterface> GetLazyStateByStatesEnum(States state);
    void InitializeState(States state);

private:
    std::map<States, std::shared_ptr<StateInterface>> states_;

    std::shared_ptr<ConsolePrinter> printer_;
    std::shared_ptr<ConsoleReader> reader_;

    std::shared_ptr<CommandFactory> command_factory_;
};


#endif //SIMPLETASKMANAGER_STATESFACTORY_H
