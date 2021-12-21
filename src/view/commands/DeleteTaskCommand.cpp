//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "DeleteTaskCommand.h"

DeleteTaskCommand::DeleteTaskCommand(const std::shared_ptr<Controller>& controller, const TaskId& task_id) :
                                    controller_(controller),
                                    task_id_(task_id) {

}
