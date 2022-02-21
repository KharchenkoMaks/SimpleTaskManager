//
// Created by Maksym Kharchenko on 24.12.2021.
//

#include "ShowState.h"
#include "utilities/TaskConvertors.h"
#include "utilities/TaskComparators.h"

void ShowState::PrintTaskWithChildren(const std::vector<RelationalTask>& tasks, const RelationalTask& task_to_print, const std::string& prefix = "") const {
    printer_->WriteLine(prefix + TaskToString(task_to_print.task_id(), task_to_print.task()));
    for (const auto& task : tasks) {
        if (task.parent_id() == task_to_print.task_id()) {
            PrintTaskWithChildren(tasks, task, prefix + "\t");
        }
    }
}

StateType ShowState::Execute(StateContext& context) {
    auto tasks = context.GetTasksToShow();
    for (const auto& task : tasks) {
        if (!task.has_parent_id()) {
            PrintTaskWithChildren(tasks, task);
        }
    }
    return next_state_;
}

ShowState::ShowState(const StateType next_state,
                     const std::shared_ptr<ConsolePrinter>& printer) :
                     next_state_(next_state),
                     printer_(printer) {}
