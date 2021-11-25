//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/InputTaskPriorityState.h"

InputTaskPriorityState::InputTaskPriorityState(const std::shared_ptr<ConsoleMultiFunctionalPrinter>& printer)
    : WizardStatePrinter(printer) {

}

std::optional<std::shared_ptr<IWizardState>> InputTaskPriorityState::Execute(std::shared_ptr<WizardContext> context,
                                                              std::shared_ptr<WizardStatesFactory> state_factory) {
    printer_->WriteLine("Please, input task priority (High, Medium, Low, None):");
    printer_->Write("Add Task> ");
    const std::string priority = printer_->ReadLine();

    try {
        Task::Priority task_priority = Task::GetTaskPriority(priority);
        context->AddTaskPriority(task_priority);
    } catch (std::invalid_argument) {
        printer_->WriteError("Wrong task priority was given, try [High, Medium, Low, None]!");
        return state_factory->GetState(WizardStatesFactory::States::kInputTaskPriority);
    }

    return state_factory->GetState(WizardStatesFactory::States::kInputTaskDueDate);
}
