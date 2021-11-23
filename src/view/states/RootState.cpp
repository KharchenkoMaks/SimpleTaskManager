//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "RootState.h"

RootState::RootState(const ConsolePrinter &printer) : WizardStatePrinter(printer) {

}

std::shared_ptr<IWizardState> RootState::Execute(std::shared_ptr<WizardContext>) {

}
