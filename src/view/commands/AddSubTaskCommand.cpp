//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "AddSubTaskCommand.h"

AddSubTaskCommand::AddSubTaskCommand(const std::shared_ptr<Controller>& controller, const Task& task,
                                     const TaskId& parent_id) :
                                     controller_(controller),
                                     task_(task),
                                     task_parent_id_(parent_id) {

}
