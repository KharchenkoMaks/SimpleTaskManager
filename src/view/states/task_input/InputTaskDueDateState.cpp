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

    std::optional<DueTime> task_due_date = DueTime::Create(user_input);
    if (task_due_date.has_value()) {
        context->AddTaskDueTime(task_due_date.value());
    } else {
        GetConsolePrinter()->WriteError("Wrong due date was given, try again!");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
    }

    return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT);
}

std::string InputTaskDueDateState::GetUserInputForDueDateEdit(const Task &task) {
    std::string user_input = GetUserInput("Due Date, default: " + task.GetDueTime().GetTimeString());
    if (user_input.empty()){
        return task.GetDueTime().GetTimeString();
    }
    return user_input;
}

std::string InputTaskDueDateState::GetUserInputForDueDateAdd() {
    return GetUserInput("Due Date, format: 12:00 01.01.2000");
}
