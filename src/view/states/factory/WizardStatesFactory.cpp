//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "WizardStatesFactory.h"

WizardStatesFactory::WizardStatesFactory() {
    root_state_ = std::shared_ptr<RootState>(new RootState(ConsolePrinter::Create()));
}

std::shared_ptr<RootState> WizardStatesFactory::CreateRootState() {
    return root_state_;
}
