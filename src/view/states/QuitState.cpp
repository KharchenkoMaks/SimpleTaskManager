//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "QuitState.h"

std::optional<std::shared_ptr<IWizardState>> QuitState::Execute(std::shared_ptr<WizardContext> context,
                                                 std::shared_ptr<WizardStatesFactory> state_factory) {
    if (UserConfirm()) {
        return std::nullopt;
    } else {
        return state_factory->GetState(WizardStatesFactory::States::kRoot);
    }
}

bool QuitState::UserConfirm() {
    std::string users_answer = GetUserInput("Are you sure? y/n");
    return users_answer == "Y" || users_answer == "y";
}

QuitState::QuitState(const std::shared_ptr<ConsolePrinter>& printer,
                     const std::shared_ptr<ConsoleReader>& reader) :
                     WizardStateConsole(printer, reader) {

}
