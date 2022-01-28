//
// Created by Maksym Kharchenko on 24.12.2021.
//

#include "ShowState.h"
#include "utilities/TaskConvertors.h"

void ShowState::PrintTasks(const std::vector<RelationalTask> &tasks) {
    for (const auto& task : tasks) {
        std::string task_string;
        if (task.has_parent_id()) {
            task_string += "\t";
        }
        task_string += TaskToString(task.task_id(), task.task());
        printer_->WriteLine(task_string);
    }
}

StateType ShowState::Execute(StateContext& context) {
    PrintTasks(context.GetTasksToShow());
    return next_state_;
}

ShowState::ShowState(const StateType next_state,
                     const std::shared_ptr<ConsolePrinter>& printer) :
                     next_state_(next_state),
                     printer_(printer) {}
