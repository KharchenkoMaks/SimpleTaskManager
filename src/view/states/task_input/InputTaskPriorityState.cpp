//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/InputTaskPriorityState.h"

InputTaskPriorityState::InputTaskPriorityState(const std::shared_ptr<WizardStatesFactory>& states_factory,
                                               const std::shared_ptr<ConsolePrinter>& printer,
                                               const std::shared_ptr<ConsoleReader>& reader) :
                                               WizardStateConsole(states_factory, printer, reader) {

}

std::optional<std::shared_ptr<IWizardState>> InputTaskPriorityState::Execute(std::shared_ptr<WizardContext> context) {
    const std::string priority = GetUserInput("Priority (High, Medium, Low, None)");

    try {
        Task::Priority task_priority = Task::GetTaskPriority(priority);
        context->AddTaskPriority(task_priority);
    } catch (std::invalid_argument) {
        GetConsolePrinter()->WriteError("Wrong task priority was given, try [High, Medium, Low, None]!");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
    }

    return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT);
}
