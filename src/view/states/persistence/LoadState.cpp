//
// Created by Maksym Kharchenko on 16.12.2021.
//

#include "LoadState.h"
#include "utilities/SaveLoadStatus.h"
#include "console_io/ConsoleUtilities.h"

LoadState::LoadState(const std::shared_ptr<StatesFactory>& factory) : factory_(factory) {

}

std::shared_ptr<StateInterface> LoadState::Execute(std::shared_ptr<StateContext> context) {
    std::string file_name = console_io::util::GetUserInput("File name", *factory_.lock()->GetConsolePrinter(), *factory_.lock()->GetConsoleReader());
    switch (factory_.lock()->GetController()->LoadFromFile(file_name)) {
        case persistence::SaveLoadStatus::SUCCESS: {
            factory_.lock()->GetConsolePrinter()->WriteLine("Tasks were successfully loaded!");
            break;
        }
        case persistence::SaveLoadStatus::FILE_WAS_NOT_OPENED: {
            factory_.lock()->GetConsolePrinter()->WriteError("Couldn't open file " + file_name + ", try again!");
            break;
        }
        case persistence::SaveLoadStatus::INVALID_FILE_STRUCTURE: {
            factory_.lock()->GetConsolePrinter()->WriteError("Couldn't load from file, " + file_name + " is damaged.");
            break;
        }
    }
    return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::PREVIOUS);
}
