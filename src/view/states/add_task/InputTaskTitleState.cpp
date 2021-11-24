//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "InputTaskTitleState.h"

InputTaskTitleState::InputTaskTitleState(std::shared_ptr<ConsolePrinter> printer) : WizardStatePrinter(printer) {

}

std::shared_ptr<IWizardState> InputTaskTitleState::Execute(std::shared_ptr<WizardContext> context,
                                                           std::shared_ptr<WizardStatesFactory> state_factory) {
    printer_->WriteLine("Please, input task title:");
    printer_->Write("Add Task> ");
    const std::string task_title = printer_->ReadLine();

    try {
        context->AddTaskTitle(task_title);
    } catch (std::invalid_argument) {
        printer_->WriteError("Task title was wrong, please, try again!");
        return state_factory->GetState(WizardStatesFactory::States::kInputTaskTitle);
    }

    return state_factory->GetState(WizardStatesFactory::States::kInputTaskPriority);
}
