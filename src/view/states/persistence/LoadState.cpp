//
// Created by Maksym Kharchenko on 16.12.2021.
//

#include "LoadState.h"

LoadState::LoadState(std::unique_ptr<StateDependencies> dependencies) : dependencies_(std::move(dependencies)) {

}

std::shared_ptr<WizardStateInterface> LoadState::Execute(std::shared_ptr<WizardContext> context) {
    std::string file_name = dependencies_->GetUserInput("File name");
    switch (dependencies_->GetController()->LoadFromFile(file_name)) {
        case TaskManagerPersistence::SaveLoadStatus::SUCCESS: {
            dependencies_->GetConsolePrinter()->WriteLine("Tasks were successfully loaded!");
            break;
        }
        case TaskManagerPersistence::SaveLoadStatus::FILE_WAS_NOT_OPENED: {
            dependencies_->GetConsolePrinter()->WriteError("Couldn't open file " + file_name + ", try again!");
            break;
        }
        case TaskManagerPersistence::SaveLoadStatus::INVALID_FILE_STRUCTURE: {
            dependencies_->GetConsolePrinter()->WriteError("Couldn't load from file, " + file_name + " is damaged.");
            break;
        }
    }
    return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
}
