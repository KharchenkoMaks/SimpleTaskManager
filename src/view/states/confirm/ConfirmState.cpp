//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "ConfirmState.h"

ConfirmState::ConfirmState(std::shared_ptr<ConsolePrinter> printer) : WizardStatePrinter(printer) {

}

std::shared_ptr<IWizardState> ConfirmState::Execute(std::shared_ptr<WizardContext> context,
                      std::shared_ptr<WizardStatesFactory> state_factory) {
    std::optional<std::string> confirm_message = context->GetConfirmMessage();

    // Printing confirmation message, or default message
    std::string default_confirm_message = "Are you sure?";
    printer_->WriteLine(confirm_message.value_or(default_confirm_message));
    context->ResetConfirmMessage();
    printer_->Write("y/n>");

    std::string answer = printer_->ReadLine();

    if (IsMessageConfirmed(answer)){
        context->ConfirmAction();
    } else {
        printer_->WriteLine("Aborting action....");
        context->NotConfirmAction();
    }
    return state_factory->GetQuitState();
}

bool ConfirmState::IsMessageConfirmed(const std::string& message) {
    return message == "y" || message == "Y"
}
