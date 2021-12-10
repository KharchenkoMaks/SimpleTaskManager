//
// Created by Maksym Kharchenko on 23.11.2021.
//

#include "RootState.h"

RootState::RootState(std::unique_ptr<StateDependencies> dependencies) :
                    dependencies_(std::move(dependencies)) {

}

std::shared_ptr<WizardStateInterface> RootState::Execute(std::shared_ptr<WizardContext> context) {
    std::string command = dependencies_->GetUserInput("");
    std::shared_ptr<WizardStateInterface> next_state =
            dependencies_->GetStatesFactory()->GetStateByCommand(command);
    if (next_state) {
        return next_state;
    } else {
        dependencies_->GetConsolePrinter()->WriteError("Unknown command! Use help.");
        return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
    }
}
