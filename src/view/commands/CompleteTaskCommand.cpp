//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "CompleteTaskCommand.h"

CompleteTaskCommand::CompleteTaskCommand(const TaskId& task_id) :
                                         task_id_(task_id) {

}

CommandResult CompleteTaskCommand::Execute(const std::shared_ptr<Controller>& controller) {
    ControllerRequestResult complete_result = controller->CompleteTask(task_id_);

    return CommandResult::Create(complete_result);
}
