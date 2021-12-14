//
// Created by Maksym Kharchenko on 24.11.2021.
//

#include "states/task_input/InputTaskPriorityState.h"
#include "utilities/TaskUtilities.h"

InputTaskPriorityState::InputTaskPriorityState(std::unique_ptr<StateDependencies> dependencies) :
                                                dependencies_(std::move(dependencies)) {

}

std::shared_ptr<WizardStateInterface> InputTaskPriorityState::Execute(std::shared_ptr<WizardContext> context) {
    std::string user_input;

    if (context->GetTaskId().has_value()) {
        user_input = GetUserInputForPriorityEdit(context->GetTask().value());
    } else {
        user_input = GetUserInputForPriorityAdd();
    }

    std::optional<Task::Priority> task_priority = StringToTaskPriority(user_input);
    if (task_priority.has_value()) {
        context->AddTaskPriority(task_priority.value());
    } else {
        dependencies_->GetConsolePrinter()->WriteError("Wrong task priority was given, try [High, Medium, Low, None]!");
        return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::ERROR);
    }

    return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT);
}

std::string InputTaskPriorityState::GetUserInputForPriorityAdd() {
    return dependencies_->GetUserInput("Priority (High, Medium, Low, None)");
}

std::string InputTaskPriorityState::GetUserInputForPriorityEdit(const Task &task) {
    std::string user_input = dependencies_->GetUserInput("Priority, default: " + TaskPriorityToString(task.priority()));
    if (user_input.empty()){
        return TaskPriorityToString(task.priority());
    }
    return user_input;
}
