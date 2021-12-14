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
        if (task.has_parent_id()) {
            task_string += "\t";
        }
        dependencies_->GetConsolePrinter()->WriteLine(TaskToString(task.task_id(), task.task()));
    }
}

std::string ShowState::TaskToString(const TaskId& task_id, const Task& task) {
    std::string return_string = "ID: " + std::to_string(task_id.id())
                                + ", Title:" + task.title()
                                + ", Priority" + TaskPriorityToString(task.priority())
                                + ", Due to: " + task.due_date().ShortDebugString()
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

std::string ShowState::TaskPriorityToString(Task::Priority priority) {
    switch(priority) {
        case Task::Priority::Task_Priority_NONE: {
            return "None";
        }
        case Task::Priority::Task_Priority_LOW: {
            return "Low";
        }
        case Task::Priority::Task_Priority_MEDIUM: {
            return "Medium";
        }
        case Task::Priority::Task_Priority_HIGH: {
            return "High";
        }
    }
}
