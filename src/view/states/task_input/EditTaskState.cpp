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
        context->SetEditingTaskId(GetUserInput("Edit Task ID"));
    } catch (std::invalid_argument) {
        GetConsolePrinter()->WriteError("Wrong task id was given, try again!");
        return state_factory->GetState(WizardStatesFactory::States::kEditTask);
    }

    std::shared_ptr<WizardContext> context_with_edited_task = std::make_shared<WizardContext>();
    ConsoleStateMachine state_machine;
    state_machine.Run(WizardStatesFactory::States::kInputTaskTitle,
                      context_with_edited_task,
                      state_factory);

    context->AddTaskTitle(context_with_edited_task->GetAddedTask().GetTitle());
    context->AddTaskPriority(context_with_edited_task->GetAddedTask().GetPriority());
    context->AddTaskDueTime(context_with_edited_task->GetAddedTask().GetDueTime());

    return state_factory->GetState(WizardStatesFactory::States::kRoot);
}
