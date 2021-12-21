//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "EditTaskCommand.h"

EditTaskCommand::EditTaskCommand(const std::shared_ptr<Controller>& controller, const Task& task,
                                 const TaskId& task_id) :
                                 controller_(controller),
                                 task_(task),
                                 task_id_(task_id) {

}
