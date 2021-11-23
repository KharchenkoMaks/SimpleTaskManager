//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "HelpState.h"

HelpState::HelpState(const ConsolePrinter &printer) : WizardStatePrinter(printer) {

}

std::shared_ptr<IWizardState> HelpState::Execute(std::shared_ptr<WizardContext> context) {
    printer_.WriteLine("Available commands:");
    printer_.WriteLine("1. add");
    printer_.WriteLine("2. edit");
    printer_.WriteLine("3. delete");
    printer_.WriteLine("4. complete");
    printer_.WriteLine("5. show");
    printer_.WriteLine("6. quit");

    return context->GetFactory()->CreateRootState();
}
