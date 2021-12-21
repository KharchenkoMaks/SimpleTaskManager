//
// Created by Maksym Kharchenko on 30.11.2021.
//

#include "ShowState.h"
#include "utilities/TaskUtilities.h"
#include "console_io/ConsoleUtilities.h"

ShowState::ShowState(const std::shared_ptr<StatesFactory>& factory) :
                    factory_(factory) {

}

std::shared_ptr<StateInterface> ShowState::Execute(std::shared_ptr<StateContext> context) {
    std::vector<TaskTransfer> tasks = factory_.lock()->GetController()->GetAllTasks();
    PrintTasks(tasks);
    return factory_.lock()->GetNextState(*this, StatesFactory::MoveType::NEXT);
}

void ShowState::PrintTasks(const std::vector<TaskTransfer>& tasks) {
    for (auto task : tasks) {
        std::string task_string;
        if (task.has_parent_id()) {
            task_string += "\t";
        }
        task_string += TaskToString(task.task_id(), task.task());
        factory_.lock()->GetConsolePrinter()->WriteLine(task_string);
    }
}
