//
// Created by Maksym Kharchenko on 25.11.2021.
//

#include "states/task_input/EditTaskState.h"
#include "ConsoleStateMachine.h"

EditTaskState::EditTaskState(const std::shared_ptr<ConsolePrinter>& printer,
                             const std::shared_ptr<ConsoleReader>& reader) :
                             WizardStateConsole(printer, reader) {

}

std::optional<std::shared_ptr<IWizardState>> EditTaskState::Execute(std::shared_ptr<WizardContext> context,
                                                     std::shared_ptr<WizardStatesFactory> state_factory) {
    try {
        context->SetEditingTaskId(InputTaskIdToEdit());
    } catch (std::invalid_argument) {
        GetConsolePrinter()->WriteLine("Wrong task id was given, try again!");
        return state_factory->GetState(WizardStatesFactory::States::kEditTask);
    }

    ConsoleStateMachine state_machine;
    WizardContext new_context = state_machine.Run(WizardStatesFactory::States::kInputTaskTitle);

    context->AddTaskTitle(new_context.GetAddedTask().GetTitle());
    context->AddTaskPriority(new_context.GetAddedTask().GetPriority());
    context->AddTaskDueTime(new_context.GetAddedTask().GetDueTime());

    return state_factory->GetState(WizardStatesFactory::States::kRoot);
}

std::string EditTaskState::InputTaskIdToEdit() {
    GetConsolePrinter()->WriteLine("Please, input id of task you want to edit:");
    GetConsolePrinter()->Write("Edit Task> ");
    std::string task_id_to_edit = GetConsoleReader()->ReadLine();
    return task_id_to_edit;
}
