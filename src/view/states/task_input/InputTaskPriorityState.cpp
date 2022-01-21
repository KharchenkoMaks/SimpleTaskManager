//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/InputTaskPriorityState.h"
#include "utilities/TaskConvertors.h"
#include "user_interface/console_io/ConsoleUtilities.h"

InputTaskPriorityState::InputTaskPriorityState(const std::shared_ptr<StatesFactory>& factory) :
                                                factory_(factory) {

}

std::shared_ptr<State> InputTaskPriorityState::Execute(StateContext& context) {
    std::string user_input =
            console_io::util::GetUserInput("Priority (High, Medium, Low, None)", *factory_->GetConsolePrinter(), *factory_->GetConsoleReader());

    std::optional<Task::Priority> task_priority = StringToTaskPriority(user_input);
    if (task_priority.has_value()) {
        context.AddTaskPriority(task_priority.value());
    } else if (!user_input.empty()) {
        factory_->GetConsolePrinter()->WriteError("Wrong task priority was given, try [High, Medium, Low, None]!");
        return factory_->GetNextState(*this, StatesFactory::MoveType::ERROR);
    }

    return factory_->GetNextState(*this, StatesFactory::MoveType::NEXT);
}
