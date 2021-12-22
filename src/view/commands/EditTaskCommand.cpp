//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "EditTaskCommand.h"

EditTaskCommand::EditTaskCommand(const TaskBuilder& task_builder,
                                 const TaskId& task_id) :
                                 task_builder_(task_builder),
                                 task_id_(task_id) {

}
