//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "HelpState.h"

HelpState::HelpState(const std::shared_ptr<WizardStatesFactory>& factory) :
                    factory_(factory) {

}

std::shared_ptr<WizardStateInterface> HelpState::Execute(std::shared_ptr<WizardContext> context) {
    factory_.lock()->GetConsolePrinter()->WriteLine("Available commands:");
    factory_.lock()->GetConsolePrinter()->WriteLine("1. add");
    factory_.lock()->GetConsolePrinter()->WriteLine("2. add_subtask");
    factory_.lock()->GetConsolePrinter()->WriteLine("3. edit");
    factory_.lock()->GetConsolePrinter()->WriteLine("4. delete");
    factory_.lock()->GetConsolePrinter()->WriteLine("5. complete");
    factory_.lock()->GetConsolePrinter()->WriteLine("6. label");
    factory_.lock()->GetConsolePrinter()->WriteLine("7. show");
    factory_.lock()->GetConsolePrinter()->WriteLine("8. save");
    factory_.lock()->GetConsolePrinter()->WriteLine("9. load");
    factory_.lock()->GetConsolePrinter()->WriteLine("10. quit");

    return factory_.lock()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT);
}
