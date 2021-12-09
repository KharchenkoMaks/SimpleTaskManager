//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "QuitState.h"

std::shared_ptr<WizardStateConsole> QuitState::Execute(std::shared_ptr<WizardContext> context) {
    if (UserConfirm()) {
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT);
    } else {
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
    }
}

QuitState::QuitState(const std::shared_ptr<WizardStatesFactory>& states_factory,
                     const std::shared_ptr<ConsolePrinter>& printer,
                     const std::shared_ptr<ConsoleReader>& reader) :
                     WizardStateConsole(states_factory, printer, reader) {

}
