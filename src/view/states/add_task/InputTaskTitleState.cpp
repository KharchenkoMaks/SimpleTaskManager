//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "InputTaskTitleState.h"

InputTaskTitleState::InputTaskTitleState(std::shared_ptr<ConsolePrinter> printer) : WizardStatePrinter(printer) {

}

std::shared_ptr<IWizardState> InputTaskTitleState::Execute(std::shared_ptr<WizardContext> context,
                                                           std::shared_ptr<WizardStatesFactory> state_factory) {

}
