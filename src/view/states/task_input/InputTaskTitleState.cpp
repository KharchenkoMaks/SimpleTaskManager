//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/InputTaskTitleState.h"

InputTaskTitleState::InputTaskTitleState(const std::shared_ptr<ConsolePrinter>& printer,
                                         const std::shared_ptr<ConsoleReader>& reader) :
                                         WizardStateConsole(printer, reader) {

}

std::optional<std::shared_ptr<IWizardState>> InputTaskTitleState::Execute(std::shared_ptr<WizardContext> context,
                                                           std::shared_ptr<WizardStatesFactory> state_factory) {
    console_printer_->WriteLine("Please, input task title:");
    console_printer_->Write("Add Task> ");
    const std::string task_title = console_reader_->ReadLine();

    try {
        context->AddTaskTitle(task_title);
    } catch (std::invalid_argument) {
        console_printer_->WriteError("Task title was wrong, please, try again!");
        return state_factory->GetState(WizardStatesFactory::States::kInputTaskTitle);
    }

    return state_factory->GetState(WizardStatesFactory::States::kInputTaskPriority);
}
