//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/InputTaskDueDateState.h"

InputTaskDueDateState::InputTaskDueDateState(const std::shared_ptr<ConsolePrinter>& printer,
                                             const std::shared_ptr<ConsoleReader>& reader) :
                                             WizardStatePrinter(printer, reader) {

}

std::optional<std::shared_ptr<IWizardState>> InputTaskDueDateState::Execute(std::shared_ptr<WizardContext> context,
                                                             std::shared_ptr<WizardStatesFactory> state_factory) {
    console_printer_->WriteLine("Please, input task due date:");
    console_printer_->Write("Add Task> ");
    const std::string due_date = console_reader_->ReadLine();

    try {
        time_t task_due_date = std::stoi(due_date);
        context->AddTaskDueTime(task_due_date);
    } catch (std::invalid_argument) {
        console_printer_->WriteError("Wrong due date was given, please, try again!");
        return state_factory->GetState(WizardStatesFactory::States::kInputTaskDueDate);
    }

    return std::nullopt;
}
