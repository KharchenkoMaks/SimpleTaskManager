//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "WizardStateConsole.h"

WizardStateConsole::WizardStateConsole(const std::shared_ptr<WizardStatesFactory>& states_factory,
                                       const std::shared_ptr<ConsolePrinter>& printer,
                                       const std::shared_ptr<ConsoleReader>& reader) :
                                       states_factory_(states_factory),
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
    std::string user_input = console_reader_->ReadLine();
    return user_input;
}

std::shared_ptr<WizardStatesFactory> WizardStateConsole::GetStatesFactory() const {
    return states_factory_.lock();
}

bool WizardStateConsole::UserConfirm(const std::string& question_string) {
    std::string users_answer = GetUserInput(question_string + " y/n");
    return users_answer == "Y" || users_answer == "y";
}

std::optional<TaskId> WizardStateConsole::GetTaskIdFromUser(const std::string& invitation_string) {
    std::string task_id_str = GetUserInput(invitation_string);
    return TaskId::Create(task_id_str);
}
