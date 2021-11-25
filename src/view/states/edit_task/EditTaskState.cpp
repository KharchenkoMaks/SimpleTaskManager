//
// Created by Maksym Kharchenko on 25.11.2021.
//

#include "EditTaskState.h"

EditTaskState::EditTaskState(std::shared_ptr<ConsolePrinter> printer) : WizardStatePrinter(printer) {

}

std::shared_ptr<IWizardState> EditTaskState::Execute(std::shared_ptr<WizardContext> context,
                                                     std::shared_ptr<WizardStatesFactory> state_factory) {
    try {
        context->SetEditingTaskId(InputTaskIdToEdit());
    } catch (std::invalid_argument) {
        printer_->WriteLine("Wrong task id was given, try again!");
        return state_factory->GetState(WizardStatesFactory::States::kEditTask);
    }

    std::shared_ptr<WizardContext> new_context =
            RunStateMachineToEditTask(context->GetAddedTask().value());

    if (new_context->GetAddedTask().has_value()) {
        context->AddTask(new_context->GetAddedTask());
        new_context->ResetAddedTask();
        // TODO (Maksym): make task editing in TaskManager
    } else {
        throw std::runtime_error("Task editing failed.");
    }

    return state_factory->GetState(WizardStatesFactory::States::kRoot);
}

std::string EditTaskState::InputTaskIdToEdit() {
    printer_->WriteLine("Please, input id of task you want to edit:");
    printer_->Write("Edit Task> ");
    std::string task_id_to_edit;
    std::cin >> task_id_to_edit;
    return task_id_to_edit;
}

std::shared_ptr<WizardContext> EditTaskState::RunStateMachineToEditTask(const Task& task_to_edit) {
    // TODO (Maksym): make ConsoleStateMachine instead of this while loop
    std::shared_ptr<WizardStatesFactory> new_factory = std::make_shared<WizardStatesFactory>();
    std::shared_ptr<WizardContext> new_context = std::make_shared<WizardContext>();
    std::shared_ptr<IWizardState> new_state =
            new_factory->GetState(WizardStatesFactory::States::kInputTaskTitle);
    new_context->AddTask(task_to_edit);

    while (!new_context->IsStateMachineStopped()){
        new_state = new_state->Execute(new_context, new_factory);
    }

    return new_context
}
