//
// Created by Maksym Kharchenko on 29.11.2021.
//

#include "IWizardState.h"

IWizardState::IWizardState(std::shared_ptr<WizardStatesFactory> states_factory) : states_factory_(states_factory) {

}
