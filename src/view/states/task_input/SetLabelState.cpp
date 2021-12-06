//
// Created by Maksym Kharchenko on 06.12.2021.
//

#include "SetLabelState.h"

SetLabelState::SetLabelState(const std::shared_ptr<Controller> &controller,
                             const std::shared_ptr<WizardStatesFactory> &states_factory,
                             const std::shared_ptr<ConsolePrinter> &printer,
                             const std::shared_ptr<ConsoleReader> &reader) :
                             WizardStateController(controller,
                                                   states_factory,
                                                   printer,
                                                   reader) {

}

std::optional<std::shared_ptr<WizardStateConsole>> SetLabelState::Execute(std::shared_ptr<WizardContext> context) {

}
