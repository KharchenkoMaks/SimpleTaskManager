//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "WizardContext.h"

std::shared_ptr<WizardStatesFactory> WizardContext::GetFactory() {
    return states_factory_;
}

WizardContext::WizardContext(std::shared_ptr<WizardStatesFactory> factory) : states_factory_(factory) {

}
