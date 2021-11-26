//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/InputTaskDueDateState.h"

InputTaskDueDateState::InputTaskDueDateState(const std::shared_ptr<ConsolePrinter>& printer,
                                             const std::shared_ptr<ConsoleReader>& reader) :
                                             WizardStateConsole(printer, reader) {

}

std::optional<std::shared_ptr<IWizardState>> InputTaskDueDateState::Execute(std::shared_ptr<WizardContext> context,
                                                             std::shared_ptr<WizardStatesFactory> state_factory) {
    const std::string due_date = GetUserInput("Due Date");

    try {
        time_t task_due_date = std::stoi(due_date);
        context->AddTaskDueTime(task_due_date);
    } catch (std::invalid_argument) {
        GetConsolePrinter()->WriteError("Wrong due date was given, please, try again!");
        return state_factory->GetState(WizardStatesFactory::States::kInputTaskDueDate);
    }

    return std::nullopt;
}
