//
// Created by Maksym Kharchenko on 16.12.2021.
//

#include "SaveState.h"
#include "utilities/SaveLoadStatus.h"
#include "user_interface/console_io/ConsoleUtilities.h"

SaveState::SaveState(const std::shared_ptr<StatesFactory>& factory) : factory_(factory) {

}

std::shared_ptr<State> SaveState::Execute(StateContext& context) {
    std::string file_name = console_io::util::GetUserInput("File name", *factory_->GetConsolePrinter(), *factory_->GetConsoleReader());
    if (file_name.empty()) {
        factory_->GetConsolePrinter()->WriteError("Invalid file name!");
        return factory_->GetNextState(*this, StatesFactory::MoveType::ERROR);
    }
    context.SetFileName(file_name);
    context.SetCommand(factory_->GetCommandFactory()->CreateSaveCommand(context));
    return factory_->GetNextState(*this, StatesFactory::MoveType::NEXT);
}
