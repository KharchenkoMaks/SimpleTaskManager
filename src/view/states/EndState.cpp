//
// Created by Maksym Kharchenko on 09.12.2021.
//

#include "EndState.h"

EndState::EndState(std::unique_ptr<StateDependencies> dependencies) :
                    dependencies_(std::move(dependencies)) {

}

std::shared_ptr<WizardStateInterface> EndState::Execute(std::shared_ptr<WizardContext> context) {
    return nullptr;
}
