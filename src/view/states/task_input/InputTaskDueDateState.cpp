//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/InputTaskDueDateState.h"

InputTaskDueDateState::InputTaskDueDateState(std::unique_ptr<StateDependencies> dependencies) :
                                             dependencies_(std::move(dependencies)) {

}

std::shared_ptr<WizardStateInterface> InputTaskDueDateState::Execute(std::shared_ptr<WizardContext> context) {
    std::string user_input;
    if (context->GetTaskId().has_value()) {
        // If TaskId has value in context, then we are editing task
        user_input = GetUserInputForDueDateEdit(context->GetTask().value());
    } else {
        // If TaskId is nullopt, then we are adding new task
        user_input = GetUserInputForDueDateAdd();
    }

    std::optional<DueTime> task_due_date = DueTime::Create(user_input);
    if (task_due_date.has_value()) {
        context->AddTaskDueTime(task_due_date.value());
    } else {
        dependencies_->GetConsolePrinter()->WriteError("Wrong due date was given, try again!");
        return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
    }

    return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT);
}

std::string InputTaskDueDateState::GetUserInputForDueDateEdit(const Task &task) {
    std::string user_input = dependencies_->GetUserInput("Due Date, default: " + task.GetDueTime().GetTimeString());
    if (user_input.empty()){
        return task.GetDueTime().GetTimeString();
    }
    return user_input;
}

std::string InputTaskDueDateState::GetUserInputForDueDateAdd() {
    return dependencies_->GetUserInput("Due Date, format: 12:00 01.01.2000");
}
