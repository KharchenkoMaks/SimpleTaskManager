//
// Created by Maksym Kharchenko on 30.11.2021.
//

#include "ShowState.h"
#include "utilities/DueDateUtilities.h"
#include "utilities/TaskPriorityUtilities.h"

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
        if (task.has_parent_id()) {
            task_string += "\t";
        }
        task_string += TaskToString(task.task_id(), task.task());
        dependencies_->GetConsolePrinter()->WriteLine(task_string);
    }
}

std::string ShowState::TaskToString(const TaskId& task_id, const Task& task) {
    std::string return_string = "ID: " + std::to_string(task_id.id())
                                + ", Title:" + task.title()
                                + ", Priority" + TaskPriorityToString(task.priority())
                                + ", Due to: " + TimeToString(task.due_date())
                                + ", Completed: ";
    if (task.completed()) {
        return_string += "Yes";
    } else {
        return_string += "No";
    }
    if (!task.label().empty()) {
        return_string += ", Label: " + task.label();
    }
    return return_string;
}
