//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "DeleteTaskCommand.h"

DeleteTaskCommand::DeleteTaskCommand(const TaskId& task_id, const bool force_delete_subtasks) :
                                     task_id_(task_id),
                                     force_delete_subtasks_(force_delete_subtasks) {

}

CommandResult DeleteTaskCommand::Execute(const std::shared_ptr<ModelController>& controller) {
    ControllerRequestResult delete_task_result;
    if (force_delete_subtasks_) {
        delete_task_result = controller->DeleteTaskWithSubTasks(task_id_);
    } else {
        delete_task_result = controller->DeleteTask(task_id_);
    }
    return CommandResult::Create(delete_task_result);
}
