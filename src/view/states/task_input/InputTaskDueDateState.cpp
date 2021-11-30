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
    const std::string due_date = GetUserInput("Due Date");

    try {
        time_t task_due_date = std::stoi(due_date);
        context->AddTaskDueTime(task_due_date);
    } catch (std::invalid_argument) {
        GetConsolePrinter()->WriteError("Wrong due date was given, please, try again!");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
    }

    return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT);
}
