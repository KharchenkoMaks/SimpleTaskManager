//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/InputTaskTitleState.h"

InputTaskTitleState::InputTaskTitleState(const std::shared_ptr<WizardStatesFactory>& states_factory,
                                         const std::shared_ptr<ConsolePrinter>& printer,
                                         const std::shared_ptr<ConsoleReader>& reader) :
                                         WizardStateConsole(states_factory, printer, reader) {

}

std::optional<std::shared_ptr<IWizardState>> InputTaskTitleState::Execute(std::shared_ptr<WizardContext> context) {
    const std::string task_title = GetUserInput("Title");

    try {
        context->AddTaskTitle(task_title);
    } catch (std::invalid_argument) {
        GetConsolePrinter()->WriteError("Task title was wrong, please, try again!");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
    }

    return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT);
}
