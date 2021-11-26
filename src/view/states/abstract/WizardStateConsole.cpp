//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "WizardStateConsole.h"

WizardStateConsole::WizardStateConsole(const std::shared_ptr<ConsolePrinter>& printer,
                                       const std::shared_ptr<ConsoleReader>& reader) :
                                       console_printer_(printer),
                                       console_reader_(reader) {

}

const std::shared_ptr<ConsolePrinter>& WizardStateConsole::GetConsolePrinter() const {
    return console_printer_;
}

const std::shared_ptr<ConsoleReader> &WizardStateConsole::GetConsoleReader() const {
    return console_reader_;
}
