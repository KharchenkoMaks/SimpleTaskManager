//
// Created by Maksym Kharchenko on 17.01.2022.
//

#include "InputSortByLabelState.h"
#include "view/user_interface/console_io/ConsoleUtilities.h"

InputSortByLabelState::InputSortByLabelState(const std::shared_ptr<StatesFactory>& factory) : factory_(factory) {}

std::shared_ptr<State> InputSortByLabelState::Execute(StateContext& context) {
    const std::string users_label =
            console_io::util::GetUserInput("Label to sort by", *factory_.lock()->GetConsolePrinter(), *factory_.lock()->GetConsoleReader());

    context.SetTaskLabel(users_label);
    return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::NEXT);
}
