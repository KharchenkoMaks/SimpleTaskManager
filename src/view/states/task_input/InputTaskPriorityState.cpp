//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/InputTaskPriorityState.h"

InputTaskPriorityState::InputTaskPriorityState(const std::shared_ptr<ConsolePrinter>& printer,
                                               const std::shared_ptr<ConsoleReader>& reader) :
                                               WizardStateConsole(printer, reader) {

}

std::optional<std::shared_ptr<IWizardState>> InputTaskPriorityState::Execute(std::shared_ptr<WizardContext> context,
                                                              std::shared_ptr<WizardStatesFactory> state_factory) {
    GetConsolePrinter()->WriteLine("Please, input task priority (High, Medium, Low, None):");
    GetConsolePrinter()->Write("Add Task> ");
    const std::string priority = GetConsoleReader()->ReadLine();

    try {
        Task::Priority task_priority = Task::GetTaskPriority(priority);
        context->AddTaskPriority(task_priority);
    } catch (std::invalid_argument) {
        GetConsolePrinter()->WriteError("Wrong task priority was given, try [High, Medium, Low, None]!");
        return state_factory->GetState(WizardStatesFactory::States::kInputTaskPriority);
    }

    return state_factory->GetState(WizardStatesFactory::States::kInputTaskDueDate);
}
