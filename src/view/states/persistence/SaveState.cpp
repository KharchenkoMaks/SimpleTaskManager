//
// Created by Maksym Kharchenko on 16.12.2021.
//

#include "SaveState.h"
#include "utilities/SaveLoadStatus.h"
#include "user_interface/console_io/ConsoleUtilities.h"

SaveState::SaveState(const std::shared_ptr<StatesFactory>& factory) : factory_(factory) {

}

std::shared_ptr<StateInterface> SaveState::Execute(StateContext& context) {
    std::string file_name = console_io::util::GetUserInput("File name", *factory_.lock()->GetConsolePrinter(), *factory_.lock()->GetConsoleReader());
    context.SetFileName(file_name);
    context.SetCommand(factory_.lock()->GetCommandFactory()->CreateSaveCommand(context));
    return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::NEXT);
}
