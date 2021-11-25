//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "states/quit/QuitState.h"

std::optional<std::shared_ptr<IWizardState>> QuitState::Execute(std::shared_ptr<WizardContext> context,
                                                 std::shared_ptr<WizardStatesFactory> state_factory) {
    if (UserConfirm()) {
        return std::nullopt;
    } else {
        return state_factory->GetState(WizardStatesFactory::States::kQuit);
    }
}

bool QuitState::UserConfirm() {
    printer_->WriteLine("Are you sure you want to quit?");
    printer_->Write("Y/N> ");
    std::string users_answer = printer_->ReadLine();
    return users_answer == "Y" || users_answer == "y";
}

QuitState::QuitState(const std::shared_ptr<ConsolePrinter>& printer) : WizardStatePrinter(printer) {

}
