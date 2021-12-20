//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "QuitState.h"
#include "console_io/ConsoleUtilities.h"

std::shared_ptr<WizardStateInterface> QuitState::Execute(std::shared_ptr<WizardContext> context) {
    if (console_io::util::UserConfirm("Are you sure?", *factory_.lock()->GetConsolePrinter(), *factory_.lock()->GetConsoleReader())) {
        return factory_.lock()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT);
    } else {
        return factory_.lock()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
    }
}

QuitState::QuitState(const std::shared_ptr<WizardStatesFactory>& factory) :
                    factory_(factory) {

}
