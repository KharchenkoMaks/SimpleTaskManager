//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "AddTaskCommand.h"

AddTaskCommand::AddTaskCommand(const Task& task) :
                               task_(task) {

}

CommandResult AddTaskCommand::Execute(const std::shared_ptr<Controller>& controller) {
    std::pair<TaskActionResult, std::optional<TaskId>> add_task_result = controller->AddTask(task_);

    switch (add_task_result.first) {
        case TaskActionResult::SUCCESS: {
            printer_->WriteLine("Task was successfully added. Task id: " + std::to_string(add_task_result.second.value().id()));
            break;
        }
        default: {
            printer_->WriteError("Invalid task was given, try again.");
            break;
        }
    }
}
