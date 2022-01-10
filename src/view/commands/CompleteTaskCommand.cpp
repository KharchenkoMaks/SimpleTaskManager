//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "CompleteTaskCommand.h"

CompleteTaskCommand::CompleteTaskCommand(const TaskId& task_id, const bool force_complete_subtasks) :
                                         task_id_(task_id),
                                         force_complete_subtasks_(force_complete_subtasks) {

}

CommandResult CompleteTaskCommand::Execute(const std::shared_ptr<Controller>& controller) {
    ControllerRequestResult complete_result;
    if (force_complete_subtasks_) {
        complete_result = controller->CompleteTaskWithSubTasks(task_id_);
    } else {
        complete_result = controller->CompleteTask(task_id_);
    }

    return CommandResult::Create(complete_result);
}
