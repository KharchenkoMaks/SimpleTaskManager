//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "RootState.h"

RootState::RootState(std::shared_ptr<ConsolePrinter> printer) : WizardStatePrinter(printer) {

}

std::shared_ptr<IWizardState> RootState::Execute(std::shared_ptr<WizardContext> context) {
    printer_->Write("> ");
    std::string command = printer_->ReadLine();
    return context->GetFactory()->CreateStateByCommand(command);
}
