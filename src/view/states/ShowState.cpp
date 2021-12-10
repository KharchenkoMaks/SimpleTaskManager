//
// Created by Maksym Kharchenko on 30.11.2021.
//

#include "ShowState.h"

ShowState::ShowState(std::unique_ptr<StateDependencies> dependencies) :
                    dependencies_(std::move(dependencies)) {

}

std::shared_ptr<WizardStateInterface> ShowState::Execute(std::shared_ptr<WizardContext> context) {
    std::string tasks_show = dependencies_->GetController()->GetAllTasks();
    dependencies_->GetConsolePrinter()->Write(tasks_show);
    return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT);
}
