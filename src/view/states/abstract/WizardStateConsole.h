//
// Created by Maksym Kharchenko on 23.11.2021.
//

#ifndef SIMPLETASKMANAGER_WIZARDSTATECONSOLE_H
#define SIMPLETASKMANAGER_WIZARDSTATECONSOLE_H

#include "states/abstract/IWizardState.h"
#include "console_io/ConsolePrinter.h"
#include "console_io/ConsoleReader.h"

#include <memory>

class WizardStateConsole : public IWizardState {
public:
    explicit WizardStateConsole(const std::shared_ptr<WizardStatesFactory>& states_factory,
                                const std::shared_ptr<ConsolePrinter>& printer,
                                const std::shared_ptr<ConsoleReader>& reader);

public:
    const std::shared_ptr<ConsolePrinter>& GetConsolePrinter() const;
    const std::shared_ptr<ConsoleReader>& GetConsoleReader() const;

public:
    std::string GetUserInput(const std::string& invitation_message);
    TaskId GetTaskIdFromUser();

public:
    virtual ~WizardStateConsole() = default;

private:
   std::shared_ptr<ConsolePrinter> console_printer_;
   std::shared_ptr<ConsoleReader> console_reader_;
};


#endif //SIMPLETASKMANAGER_WIZARDSTATECONSOLE_H
