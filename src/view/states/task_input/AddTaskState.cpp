//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/AddTaskState.h"
#include "ConsoleStateMachine.h"

std::optional<std::shared_ptr<WizardStateConsole>> AddTaskState::Execute(std::shared_ptr<WizardContext> context) {
    ConsoleStateMachine state_machine(std::make_shared<WizardContext>(),
            GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT));
    std::shared_ptr<WizardContext> context_with_added_task = state_machine.Run();

//    context->AddTaskTitle(context_with_added_task->GetAddedTask().GetTitle());
//    context->AddTaskPriority(context_with_added_task->GetAddedTask().GetPriority());
//    context->AddTaskDueTime(context_with_added_task->GetAddedTask().GetDueTime());

    // Giving task to controller
    try {
        GetController()->AddTask(context_with_added_task->GetTask().value());
    } catch (std::invalid_argument) {
        GetConsolePrinter()->WriteError("Given task wasn't saved, try again.");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
    }

    return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
}

AddTaskState::AddTaskState(const std::shared_ptr<Controller>& controller,
                           const std::shared_ptr<WizardStatesFactory>& states_factory,
                           const std::shared_ptr<ConsolePrinter>& printer,
                           const std::shared_ptr<ConsoleReader>& reader) :
                           WizardStateController(controller, states_factory, printer, reader) {

}
