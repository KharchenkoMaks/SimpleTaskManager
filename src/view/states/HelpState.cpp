//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "HelpState.h"

HelpState::HelpState(const std::shared_ptr<ConsolePrinter>& printer,
                     const std::shared_ptr<ConsoleReader>& reader) :
                     WizardStateConsole(printer, reader) {

}

std::optional<std::shared_ptr<IWizardState>> HelpState::Execute(std::shared_ptr<WizardContext> context,
                                                 std::shared_ptr<WizardStatesFactory> state_factory) {
    GetConsolePrinter()->WriteLine("Available commands:");
    GetConsolePrinter()->WriteLine("1. add");
    GetConsolePrinter()->WriteLine("2. edit");
    GetConsolePrinter()->WriteLine("3. delete");
    GetConsolePrinter()->WriteLine("4. complete");
    GetConsolePrinter()->WriteLine("5. show");
    GetConsolePrinter()->WriteLine("6. quit");

    return state_factory->GetNextState(*this, WizardStatesFactory::MoveType::NEXT);
}
