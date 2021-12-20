//
// Created by Maksym Kharchenko on 09.12.2021.
//

#include "EndState.h"

EndState::EndState(const std::shared_ptr<WizardStatesFactory>& factory) :
                    factory_(factory) {

}

std::shared_ptr<WizardStateInterface> EndState::Execute(std::shared_ptr<WizardContext> context) {
    return nullptr;
}
