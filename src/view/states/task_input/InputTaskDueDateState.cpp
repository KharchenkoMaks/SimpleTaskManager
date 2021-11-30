//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/InputTaskDueDateState.h"

InputTaskDueDateState::InputTaskDueDateState(const std::shared_ptr<WizardStatesFactory>& states_factory,
                                             const std::shared_ptr<ConsolePrinter>& printer,
                                             const std::shared_ptr<ConsoleReader>& reader) :
                                             WizardStateConsole(states_factory, printer, reader) {

}

std::optional<std::shared_ptr<WizardStateConsole>> InputTaskDueDateState::Execute(std::shared_ptr<WizardContext> context) {
    std::string user_input;
    if (context->GetTaskId().has_value()) {
        // If TaskId has value in context, then we are editing task
        user_input = GetUserInputForDueDateEdit(context->GetTask().value());
    } else {
        // If TaskId is nullopt, then we are adding new task
        user_input = GetUserInputForDueDateAdd();
    }

    try {
        time_t task_due_date = std::stoi(user_input);
        context->AddTaskDueTime(task_due_date);
    } catch (std::invalid_argument) {
        GetConsolePrinter()->WriteError("Wrong due date was given, try again!");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
    }

    return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT);
}

std::string InputTaskDueDateState::GetUserInputForDueDateEdit(const Task &task) {
    GetConsolePrinter()->WriteLine("Leave empty for default value.");
    return GetUserInput("Due Date, default: " + std::to_string(task.GetDueTime()));
}

std::string InputTaskDueDateState::GetUserInputForDueDateAdd() {
    return GetUserInput("Due Date");
}
