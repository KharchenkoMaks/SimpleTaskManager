//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_WIZARDSTATECONSOLE_H
#define SIMPLETASKMANAGER_WIZARDSTATECONSOLE_H

#include "WizardContext.h"
#include "console_io/ConsolePrinter.h"
#include "console_io/ConsoleReader.h"
#include "id/TaskId.h"

#include <memory>
#include <optional>

class WizardStatesFactory;

class WizardStateConsole {
public:
    explicit WizardStateConsole(const std::shared_ptr<WizardStatesFactory>& states_factory,
                                const std::shared_ptr<ConsolePrinter>& printer,
                                const std::shared_ptr<ConsoleReader>& reader);

public:
    virtual std::optional<std::shared_ptr<WizardStateConsole>> Execute(std::shared_ptr<WizardContext>) = 0;

public:
    std::shared_ptr<WizardStatesFactory> GetStatesFactory() const;

    const std::shared_ptr<ConsolePrinter> &GetConsolePrinter() const;
    const std::shared_ptr<ConsoleReader> &GetConsoleReader() const;

public:
    std::string GetUserInput(const std::string &invitation_message);
    bool UserConfirm(const std::string& question_string = "Are you sure?");
    // Returns std::nullopt if invalid task_id was given
    std::optional<TaskId> GetTaskIdFromUser(const std::string& invitation_string = "Task ID");

public:
    virtual ~WizardStateConsole() = default;

private:
    std::weak_ptr<WizardStatesFactory> states_factory_;

    std::shared_ptr<ConsolePrinter> console_printer_;
    std::shared_ptr<ConsoleReader> console_reader_;
};


#endif //SIMPLETASKMANAGER_WIZARDSTATECONSOLE_H
