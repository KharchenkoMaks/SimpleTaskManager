//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "InputTaskPriorityState.h"

InputTaskPriorityState::InputTaskPriorityState(std::shared_ptr<ConsolePrinter> printer)
    : WizardStatePrinter(printer) {

}

std::shared_ptr<IWizardState> InputTaskPriorityState::Execute(std::shared_ptr<WizardContext> context,
                                                              std::shared_ptr<WizardStatesFactory> state_factory) {

}
