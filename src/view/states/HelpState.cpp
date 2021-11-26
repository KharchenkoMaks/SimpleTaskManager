//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "HelpState.h"

HelpState::HelpState(const std::shared_ptr<ConsolePrinter>& printer,
                     const std::shared_ptr<ConsoleReader>& reader) :
                     WizardStatePrinter(printer, reader) {

}

std::optional<std::shared_ptr<IWizardState>> HelpState::Execute(std::shared_ptr<WizardContext> context,
                                                 std::shared_ptr<WizardStatesFactory> state_factory) {
    console_printer_->WriteLine("Available commands:");
    console_printer_->WriteLine("1. add");
    console_printer_->WriteLine("2. edit");
    console_printer_->WriteLine("3. delete");
    console_printer_->WriteLine("4. complete");
    console_printer_->WriteLine("5. show");
    console_printer_->WriteLine("6. quit");

    return state_factory->GetState(WizardStatesFactory::States::kRoot);
}
