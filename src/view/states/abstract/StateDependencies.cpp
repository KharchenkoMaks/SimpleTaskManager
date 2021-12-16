//
// Created by Maksym Kharchenko on 10.12.2021.
//

#include "StateDependencies.h"
#include "ConsoleStateMachine.h"

std::shared_ptr<Controller> StateDependencies::GetController() {
    return controller_;
}

std::shared_ptr<ConsolePrinter> StateDependencies::GetConsolePrinter() {
    return console_printer_;
}

std::string StateDependencies::GetUserInput(const std::string& invitation_message) {
    console_printer_->Write(invitation_message + "> ");
    std::string user_input = console_reader_->ReadLine();
    return user_input;
}

std::shared_ptr<WizardStatesFactory> StateDependencies::GetStatesFactory() {
    return states_factory_.lock();
}

bool StateDependencies::UserConfirm(const std::string& question_string) {
    std::string users_answer = GetUserInput(question_string + " y/n");
    return users_answer == "Y" || users_answer == "y";
}

std::optional<TaskId> StateDependencies::GetTaskIdFromUser(const std::string& invitation_string) {
    std::string task_id_str = GetUserInput(invitation_string);
    return StringToTaskId(task_id_str);
}

std::shared_ptr<WizardContext> StateDependencies::RunStateMachine(const std::shared_ptr<WizardContext>& context,
                                                                  const std::shared_ptr<WizardStateInterface>& initial_state) {
    return state_machine_->Run(context, initial_state);
}

StateDependencies::StateDependencies(std::unique_ptr<ConsoleStateMachine> state_machine,
                                     const std::shared_ptr<WizardStatesFactory>& factory,
                                     const std::shared_ptr<Controller>& controller,
                                     const std::shared_ptr<ConsolePrinter>& printer,
                                     const std::shared_ptr<ConsoleReader>& reader) :
                                     states_factory_(factory),
                                     state_machine_(std::move(state_machine)),
                                     controller_(controller),
                                     console_printer_(printer),
                                     console_reader_(reader) {

}

StateDependencies::~StateDependencies() = default;