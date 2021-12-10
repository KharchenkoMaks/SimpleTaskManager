//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/InputTaskTitleState.h"

InputTaskTitleState::InputTaskTitleState(std::unique_ptr<StateDependencies> dependencies) :
                                        dependencies_(std::move(dependencies)) {

}

std::shared_ptr<WizardStateInterface> InputTaskTitleState::Execute(std::shared_ptr<WizardContext> context) {
    std::string user_input;

    if (context->GetTaskId().has_value()) {
        user_input = GetUserInputForTitleEdit(context->GetTask().value());
    } else {
        user_input = GetUserInputForTitleAdd();
    }

    if (!context->AddTaskTitle(user_input)) {
        dependencies_->GetConsolePrinter()->WriteError("Task title was wrong, please, try again!");
        return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
    }

    return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT);
}

std::string InputTaskTitleState::GetUserInputForTitleAdd() {
    return dependencies_->GetUserInput("Title");
}

std::string InputTaskTitleState::GetUserInputForTitleEdit(const Task &task) {
    dependencies_->GetConsolePrinter()->WriteLine("Leave empty for default value.");
    std::string user_input = dependencies_->GetUserInput("Title, default: " + task.GetTitle());
    if (user_input.empty()){
        return task.GetTitle();
    }
    return user_input;
}
