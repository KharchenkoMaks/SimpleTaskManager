//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/InputTaskPriorityState.h"
#include "utilities/TaskUtilities.h"
#include "console_io/ConsoleUtilities.h"

InputTaskPriorityState::InputTaskPriorityState(const std::shared_ptr<WizardStatesFactory>& factory) :
                                                factory_(factory) {

}

std::shared_ptr<WizardStateInterface> InputTaskPriorityState::Execute(std::shared_ptr<WizardContext> context) {
    std::string user_input;

    if (context->GetTaskId().has_value()) {
        user_input = GetUserInputForPriorityEdit(context->GetTask().value());
    } else {
        user_input = GetUserInputForPriorityAdd();
    }

    std::optional<Task::Priority> task_priority = StringToTaskPriority(user_input);
    if (task_priority.has_value()) {
        context->AddTaskPriority(task_priority.value());
    } else {
        factory_.lock()->GetConsolePrinter()->WriteError("Wrong task priority was given, try [High, Medium, Low, None]!");
        return factory_.lock()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
    }

    return factory_.lock()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT);
}

std::string InputTaskPriorityState::GetUserInputForPriorityAdd() {
    return console_io::util::GetUserInput("Priority (High, Medium, Low, None)", *factory_.lock()->GetConsolePrinter(), *factory_.lock()->GetConsoleReader());
}

std::string InputTaskPriorityState::GetUserInputForPriorityEdit(const Task &task) {
    std::string user_input = console_io::util::GetUserInput("Priority, default: " + TaskPriorityToString(task.priority()),
                                                            *factory_.lock()->GetConsolePrinter(),
                                                            *factory_.lock()->GetConsoleReader());
    if (user_input.empty()){
        return TaskPriorityToString(task.priority());
    }
    return user_input;
}
