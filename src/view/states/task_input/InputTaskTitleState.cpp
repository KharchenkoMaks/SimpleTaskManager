//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/InputTaskTitleState.h"
#include "user_interface/console_io/ConsoleUtilities.h"

InputTaskTitleState::InputTaskTitleState(const std::shared_ptr<StatesFactory>& factory) :
                                        factory_(factory) {

}

std::shared_ptr<StateInterface> InputTaskTitleState::Execute(StateContext& context) {
    std::string user_input = GetUserInputForTitleAdd();

    if (!context.AddTaskTitle(user_input)) {
        factory_.lock()->GetConsolePrinter()->WriteError("Task title was wrong, please, try again!");
        return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::ERROR);
    }

    return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::NEXT);
}

std::string InputTaskTitleState::GetUserInputForTitleAdd() {
    return console_io::util::GetUserInput("Title", *factory_.lock()->GetConsolePrinter(), *factory_.lock()->GetConsoleReader());
}
