//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "HelpState.h"

HelpState::HelpState(const std::shared_ptr<WizardStatesFactory>& states_factory,
                     const std::shared_ptr<ConsolePrinter>& printer,
                     const std::shared_ptr<ConsoleReader>& reader) :
                     WizardStateConsole(states_factory, printer, reader) {

}

std::optional<std::shared_ptr<WizardStateConsole>> HelpState::Execute(std::shared_ptr<WizardContext> context) {
    GetConsolePrinter()->WriteLine("Available commands:");
    GetConsolePrinter()->WriteLine("1. add");
    GetConsolePrinter()->WriteLine("2. add_subtask");
    GetConsolePrinter()->WriteLine("3. edit");
    GetConsolePrinter()->WriteLine("4. delete");
    GetConsolePrinter()->WriteLine("5. complete");
    GetConsolePrinter()->WriteLine("6. set_label");
    GetConsolePrinter()->WriteLine("7. show");
    GetConsolePrinter()->WriteLine("8. quit");

    return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT);
}
