//
// Created by Maksym Kharchenko on 10.12.2021.
//

#ifndef SIMPLETASKMANAGER_STATEDEPENDENCIES_H
#define SIMPLETASKMANAGER_STATEDEPENDENCIES_H

#include "WizardStateInterface.h"
#include "Controller.h"
#include "WizardContext.h"
#include "console_io/ConsolePrinter.h"
#include "console_io/ConsoleReader.h"
#include "id/TaskId.h"

class ConsoleStateMachine;
class WizardStatesFactory;

class StateDependencies {
public:
    StateDependencies(std::unique_ptr<ConsoleStateMachine> state_machine,
                      const std::shared_ptr<WizardStatesFactory>& factory,
                      const std::shared_ptr<Controller>& controller,
                      const std::shared_ptr<ConsolePrinter>& printer,
                      const std::shared_ptr<ConsoleReader>& reader);
public:
    std::shared_ptr<WizardStatesFactory> GetStatesFactory() const;

    std::shared_ptr<Controller> GetController() const;

    const std::shared_ptr<ConsolePrinter> &GetConsolePrinter() const;
    const std::shared_ptr<ConsoleReader> &GetConsoleReader() const;

public:
    std::string GetUserInput(const std::string &invitation_message);
    bool UserConfirm(const std::string& question_string = "Are you sure?");
    // Returns std::nullopt if invalid task_id was given
    std::optional<TaskId> GetTaskIdFromUser(const std::string& invitation_string = "Task ID");
public:
    std::shared_ptr<WizardContext> RunStateMachine(const std::shared_ptr<WizardContext>& context,
                                                   const std::shared_ptr<WizardStateInterface>& initial_state);
public:
    virtual ~StateDependencies();
private:
    std::weak_ptr<WizardStatesFactory> states_factory_;

    std::shared_ptr<ConsolePrinter> console_printer_;
    std::shared_ptr<ConsoleReader> console_reader_;

    std::shared_ptr<Controller> controller_;

    std::unique_ptr<ConsoleStateMachine> state_machine_;
};


#endif //SIMPLETASKMANAGER_STATEDEPENDENCIES_H
