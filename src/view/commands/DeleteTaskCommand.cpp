//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "DeleteTaskCommand.h"

DeleteTaskCommand::DeleteTaskCommand(const TaskId& task_id) :
                                     task_id_(task_id) {

}

CommandResult DeleteTaskCommand::Execute(const std::shared_ptr<Controller>& controller) {
    auto delete_task_result = controller->DeleteTask(task_id_);
    return CommandResult::Create(delete_task_result);
}
