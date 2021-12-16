//
// Created by Maksym Kharchenko on 16.12.2021.
//

#include "SaveState.h"

SaveState::SaveState(std::unique_ptr<StateDependencies> dependencies) : dependencies_(std::move(dependencies)) {

}

std::shared_ptr<WizardStateInterface> SaveState::Execute(std::shared_ptr<WizardContext> context) {
    std::string file_name = dependencies_->GetUserInput("File name");
    switch (dependencies_->GetController()->SaveToFile(file_name)) {
        case TaskManagerPersistence::SaveLoadStatus::SUCCESS: {
            dependencies_->GetConsolePrinter()->WriteLine("Tasks were successfully saved to " + file_name);
            break;
        }
        default: {
            dependencies_->GetConsolePrinter()->WriteError("Couldn't open file " + file_name + ", try again!");
            break;
        }
    }
    return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
}
