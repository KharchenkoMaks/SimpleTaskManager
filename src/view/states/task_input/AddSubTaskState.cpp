//
// Created by Maksym Kharchenko on 02.12.2021.
//

#include "AddSubTaskState.h"

AddSubTaskState::AddSubTaskState(const std::shared_ptr<ConsoleStateMachine>& state_machine,
                                const std::shared_ptr<Controller>& controller,
                                const std::shared_ptr<WizardStatesFactory>& states_factory,
                                const std::shared_ptr<ConsolePrinter>& printer,
                                const std::shared_ptr<ConsoleReader>& reader) : WizardStateWithStateMachine(state_machine,
                                                                                                            controller,
                                                                                                            states_factory,
                                                                                                            printer,
                                                                                                            reader) {

}

std::optional<std::shared_ptr<WizardStateConsole>> AddSubTaskState::Execute(std::shared_ptr<WizardContext> context) {
    WizardStateController::TaskIdFromUser parent_task_id = GetTaskIdFromUser("Parent Task ID");
    if (parent_task_id.answer_status_ == WizardStateController::TaskIdFromUser::AnswerStatus::kNotValid){
        GetConsolePrinter()->WriteError("Wrong task id was given, try again!");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
    } else if (parent_task_id.answer_status_ == WizardStateController::TaskIdFromUser::AnswerStatus::kNotValid) {
        GetConsolePrinter()->WriteError("No task with such task id was found, try again.");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
    }

    std::shared_ptr<WizardContext> context_with_added_task = RunStateMachine(std::make_shared<WizardContext>(),
                    GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT));

    std::optional<TaskId> added_subtask_id = GetController()->AddSubTask(context_with_added_task->GetTask().value(),
                                                                         parent_task_id.task_id_.value());
    if (added_subtask_id.has_value()) {
        GetConsolePrinter()->WriteLine("SubTask was successfully added. Task id: " +
                                        std::to_string(added_subtask_id.value().GetId()));

    } else {
        GetConsolePrinter()->WriteError("Given subtask wasn't saved, try again.");
        return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
    }

    return GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::PREVIOUS);
}
