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
    virtual std::shared_ptr<WizardStatesFactory> GetStatesFactory();

    virtual std::shared_ptr<Controller> GetController();

    virtual std::shared_ptr<ConsolePrinter> GetConsolePrinter();
    virtual std::shared_ptr<ConsoleReader> GetConsoleReader();

public:
    virtual std::string GetUserInput(const std::string &invitation_message);
    virtual bool UserConfirm(const std::string& question_string);
    // Returns std::nullopt if invalid task_id was given
    virtual std::optional<TaskId> GetTaskIdFromUser(const std::string& invitation_string);
public:
    virtual std::shared_ptr<WizardContext> RunStateMachine(const std::shared_ptr<WizardContext>& context,
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
