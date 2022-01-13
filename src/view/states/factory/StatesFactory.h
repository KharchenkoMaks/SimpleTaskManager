//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_STATESFACTORY_H
#define SIMPLETASKMANAGER_STATESFACTORY_H

#include "states/State.h"
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
    virtual std::shared_ptr<ConsolePrinter> GetConsolePrinter() const;
    virtual std::shared_ptr<ConsoleReader> GetConsoleReader() const;
    virtual std::shared_ptr<CommandFactory> GetCommandFactory() const;

public:
    virtual std::unique_ptr<ConsoleStateMachine> CreateStateMachine() const;

public:
    virtual std::shared_ptr<State> GetStateByCommand(const std::string& command);

    virtual std::shared_ptr<State> GetRootState();
    virtual std::shared_ptr<State> GetShowState();

    virtual std::shared_ptr<State> GetNextState(const RootState& state, MoveType move_type);
    virtual std::shared_ptr<State> GetNextState(const HelpState& state, MoveType move_type);
    virtual std::shared_ptr<State> GetNextState(const QuitState& state, MoveType move_type);
    virtual std::shared_ptr<State> GetNextState(const AddTaskState& state, MoveType move_type);
    virtual std::shared_ptr<State> GetNextState(const EditTaskState& state, MoveType move_type);
    virtual std::shared_ptr<State> GetNextState(const InputTaskTitleState& state, MoveType move_type);
    virtual std::shared_ptr<State> GetNextState(const InputTaskPriorityState& state, MoveType move_type);
    virtual std::shared_ptr<State> GetNextState(const InputTaskDueDateState& state, MoveType move_type);
    virtual std::shared_ptr<State> GetNextState(const InputShowParametersState& state, MoveType move_type);
    virtual std::shared_ptr<State> GetNextState(const CompleteTaskState& state, MoveType move_type);
    virtual std::shared_ptr<State> GetNextState(const AddSubTaskState& state, MoveType move_type);
    virtual std::shared_ptr<State> GetNextState(const DeleteTaskState& state, MoveType move_type);
    virtual std::shared_ptr<State> GetNextState(const SetLabelState& state, MoveType move_type);
    virtual std::shared_ptr<State> GetNextState(const SaveState& state, MoveType move_type);
    virtual std::shared_ptr<State> GetNextState(const LoadState& state, MoveType move_type);
    virtual std::shared_ptr<State> GetNextState(const ShowState& state, MoveType move_type);

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
    std::shared_ptr<State> GetLazyStateByStatesEnum(States state);
    void InitializeState(States state);

private:
    std::map<States, std::shared_ptr<State>> states_;

    std::shared_ptr<ConsolePrinter> printer_;
    std::shared_ptr<ConsoleReader> reader_;

    std::shared_ptr<CommandFactory> command_factory_;
};


#endif //SIMPLETASKMANAGER_STATESFACTORY_H
