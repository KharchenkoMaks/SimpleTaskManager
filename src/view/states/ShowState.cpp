//
// Created by Maksym Kharchenko on 24.12.2021.
//

#include "ShowState.h"
#include "utilities/TaskConvertors.h"

void ShowState::PrintTasks(const std::vector<RelationalTask>& tasks) {
    for (auto task : tasks) {
        std::string task_string;
        if (task.has_parent_id()) {
            task_string += "\t";
        }
        task_string += TaskToString(task.task_id(), task.task());
        factory_.lock()->GetConsolePrinter()->WriteLine(task_string);
    }
}

void ShowState::PrintTasksWithoutRelations(const std::vector<RelationalTask>& tasks) {
    for (auto task : tasks) {
        factory_.lock()->GetConsolePrinter()->WriteLine(TaskToString(task.task_id(), task.task()));
    }
}


std::shared_ptr<State> ShowState::Execute(StateContext& context) {
    if (context.GetTasksToShow().show_task_relations_)
        PrintTasks(context.GetTasksToShow().tasks_);
    else
        PrintTasksWithoutRelations(context.GetTasksToShow().tasks_);
    return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::PREVIOUS);
}

ShowState::ShowState(const std::shared_ptr<StatesFactory>& factory) : factory_(factory) {

}
