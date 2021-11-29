//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "WizardStateConsole.h"

WizardStateConsole::WizardStateConsole(const std::shared_ptr<WizardStatesFactory>& states_factory,
                                       const std::shared_ptr<ConsolePrinter>& printer,
                                       const std::shared_ptr<ConsoleReader>& reader) :
                                       IWizardState(states_factory),
                                       console_printer_(printer),
                                       console_reader_(reader) {

}

const std::shared_ptr<ConsolePrinter>& WizardStateConsole::GetConsolePrinter() const {
    return console_printer_;
}

const std::shared_ptr<ConsoleReader> &WizardStateConsole::GetConsoleReader() const {
    return console_reader_;
}

std::string WizardStateConsole::GetUserInput(const std::string& invitation_message) {
    console_printer_->Write(invitation_message + "> ");
    std::string user_input;
    std::cin >> user_input;
    return user_input;
}
