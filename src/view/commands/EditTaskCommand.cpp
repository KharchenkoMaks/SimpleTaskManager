//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "EditTaskCommand.h"

EditTaskCommand::EditTaskCommand(const std::shared_ptr<Controller>& controller,
                                 const std::shared_ptr<ConsolePrinter>& printer,
                                 const TaskBuilder& task_builder,
                                 const TaskId& task_id) :
                                 controller_(controller),
                                 printer_(printer),
                                 task_builder_(task_builder),
                                 task_id_(task_id) {

}
