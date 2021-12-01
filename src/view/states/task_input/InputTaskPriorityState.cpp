//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/InputTaskPriorityState.h"

InputTaskPriorityState::InputTaskPriorityState(const std::shared_ptr<WizardStatesFactory>& states_factory,
                                               const std::shared_ptr<ConsolePrinter>& printer,
                                               const std::shared_ptr<ConsoleReader>& reader) :
                                               WizardStateConsole(states_factory, printer, reader) {

}

std::optional<std::shared_ptr<WizardStateConsole>> InputTaskPriorityState::Execute(std::shared_ptr<WizardContext> context) {
    std::string user_input;

    if (context->GetTaskId().has_value()) {
        user_input = GetUserInputForPriorityEdit(context->GetTask().value());
    } else {
        user_input = GetUserInputForPriorityAdd();
    }

    std::optional<Task::Priority> task_priority = Task::GetTaskPriority(user_input);
    if (task_priority.has_value()) {
        context->AddTaskPriority(task_priority.value());
    } else {
        GetConsolePrinter()->WriteError("Wrong task priority was given, try [High, Medium, Low, None]!");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
    }

    return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT);
}

std::string InputTaskPriorityState::GetUserInputForPriorityAdd() {
    return GetUserInput("Priority (High, Medium, Low, None)");
}

std::string InputTaskPriorityState::GetUserInputForPriorityEdit(const Task &task) {
    std::string user_input = GetUserInput("Priority, default: " + Task::PriorityToString(task.GetPriority()));
    if (user_input.empty()){
        return Task::PriorityToString(task.GetPriority());
    }
    return user_input;
}
