//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "AddTaskCommand.h"

AddTaskCommand::AddTaskCommand(const Task& task) :
                               task_(task) {

}

CommandResult AddTaskCommand::Execute(const std::shared_ptr<ModelController>& controller) {
    auto add_task_result = controller->AddTask(task_);

    switch (add_task_result.first) {
        case ControllerRequestResult::SUCCESS: {
            return CommandResult::Create(add_task_result.second);
        }
        default: {
            return CommandResult::Create(add_task_result.first);
        }
    }
}
