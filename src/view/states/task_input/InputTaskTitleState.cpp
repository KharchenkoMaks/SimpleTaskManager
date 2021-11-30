//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/InputTaskTitleState.h"

InputTaskTitleState::InputTaskTitleState(const std::shared_ptr<WizardStatesFactory>& states_factory,
                                         const std::shared_ptr<ConsolePrinter>& printer,
                                         const std::shared_ptr<ConsoleReader>& reader) :
                                         WizardStateConsole(states_factory, printer, reader) {

}

std::optional<std::shared_ptr<WizardStateConsole>> InputTaskTitleState::Execute(std::shared_ptr<WizardContext> context) {
    std::string user_input;

    if (context->GetTaskId().has_value()) {
        user_input = GetUserInputForTitleEdit(context->GetTask().value());
    } else {
        user_input = GetUserInputForTitleAdd();
    }

    try {
        context->AddTaskTitle(user_input);
    } catch (std::invalid_argument) {
        GetConsolePrinter()->WriteError("Task title was wrong, please, try again!");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
    }

    return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT);
}

std::string InputTaskTitleState::GetUserInputForTitleAdd() {
    return GetUserInput("Title");
}

std::string InputTaskTitleState::GetUserInputForTitleEdit(const Task &task) {
    GetConsolePrinter()->WriteLine("Leave empty for default value.");
    return GetUserInput("Title, default: " + task.GetTitle());
}
