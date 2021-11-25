//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/InputTaskDueDateState.h"

InputTaskDueDateState::InputTaskDueDateState(std::shared_ptr<ConsolePrinter> printer)
    : WizardStatePrinter(printer) {

}

std::optional<std::shared_ptr<IWizardState>> InputTaskDueDateState::Execute(std::shared_ptr<WizardContext> context,
                                                             std::shared_ptr<WizardStatesFactory> state_factory) {
    printer_->WriteLine("Please, input task due date:");
    printer_->Write("Add Task> ");
    const std::string due_date = printer_->ReadLine();

    try {
        time_t task_due_date = std::stoi(due_date);
        context->AddTaskDueTime(task_due_date);
    } catch (std::invalid_argument) {
        printer_->WriteError("Wrong due date was given, please, try again!");
        return state_factory->GetState(WizardStatesFactory::States::kInputTaskDueDate);
    }

    context->InterruptStateMachine();
    return state_factory->GetState(WizardStatesFactory::States::kQuit);
}
