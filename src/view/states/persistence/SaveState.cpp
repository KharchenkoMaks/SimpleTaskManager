//
// Created by Maksym Kharchenko on 16.12.2021.
//

#include "SaveState.h"
#include "utilities/SaveLoadStatus.h"
#include "console_io/ConsoleUtilities.h"

SaveState::SaveState(const std::shared_ptr<StatesFactory>& factory) : factory_(factory) {

}

std::shared_ptr<StateInterface> SaveState::Execute(std::shared_ptr<StateContext> context) {
    std::string file_name = console_io::util::GetUserInput("File name", *factory_.lock()->GetConsolePrinter(), *factory_.lock()->GetConsoleReader());
    switch (factory_.lock()->GetController()->SaveToFile(file_name)) {
        case persistence::SaveLoadStatus::SUCCESS: {
            factory_.lock()->GetConsolePrinter()->WriteLine("Tasks were successfully saved to " + file_name);
            break;
        }
        default: {
            factory_.lock()->GetConsolePrinter()->WriteError("Couldn't open file " + file_name + ", try again!");
            break;
        }
    }
    return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::PREVIOUS);
}
