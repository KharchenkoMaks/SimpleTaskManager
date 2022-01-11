//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/InputTaskTitleState.h"
#include "user_interface/console_io/ConsoleUtilities.h"

InputTaskTitleState::InputTaskTitleState(const std::shared_ptr<StatesFactory>& factory) :
                                        factory_(factory) {

}

std::shared_ptr<StateInterface> InputTaskTitleState::Execute(StateContext& context) {
    std::string user_input =
            console_io::util::GetUserInput("Title", *factory_.lock()->GetConsolePrinter(), *factory_.lock()->GetConsoleReader());

    if (!user_input.empty())
        context.AddTaskTitle(user_input);

    return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::NEXT);
}
