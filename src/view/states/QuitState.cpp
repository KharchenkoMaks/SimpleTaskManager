//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "QuitState.h"

std::shared_ptr<WizardStateInterface> QuitState::Execute(std::shared_ptr<WizardContext> context) {
    if (dependencies_->UserConfirm()) {
        return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT);
    } else {
        return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
    }
}

QuitState::QuitState(std::unique_ptr<StateDependencies> dependencies) :
                    dependencies_(std::move(dependencies)) {

}
