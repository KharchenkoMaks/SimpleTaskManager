//
// Created by Maksym Kharchenko on 30.11.2021.
//

#include "ShowState.h"

ShowState::ShowState(std::unique_ptr<StateDependencies> dependencies) :
                    dependencies_(std::move(dependencies)) {

}

std::shared_ptr<WizardStateInterface> ShowState::Execute(std::shared_ptr<WizardContext> context) {
    std::vector<TaskTransfer> tasks = dependencies_->GetController()->GetAllTasks();
    PrintTasks(tasks);
    return dependencies_->GetStatesFactory()->GetNextState(*this, WizardStatesFactory::MoveType::NEXT);
}

void ShowState::PrintTasks(const std::vector<TaskTransfer>& tasks) {
    for (auto task : tasks) {
        std::string task_string;
        if (task.GetParentTaskId().has_value()) {
            task_string += "\t";
        }
        task_string += task.GetTaskId().to_string() + ", " + task.GetTask().to_string();
        dependencies_->GetConsolePrinter()->WriteLine(task_string);
    }
}
