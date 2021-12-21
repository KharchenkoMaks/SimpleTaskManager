//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "AddSubTaskCommand.h"

AddSubTaskCommand::AddSubTaskCommand(const std::shared_ptr<Controller>& controller,
                                     const std::shared_ptr<ConsolePrinter>& printer,
                                     const Task& task,
                                     const TaskId& parent_id) :
                                     controller_(controller),
                                     printer_(printer),
                                     task_(task),
                                     task_parent_id_(parent_id) {

}

void AddSubTaskCommand::Execute() {
    auto controller_answer = controller_->AddSubTask(task_, task_parent_id_);
    switch(controller_answer.first) {
        case TaskActionResult::SUCCESS: {
            printer_->WriteLine("Subtask was successfully added. Task id: " + std::to_string(controller_answer.second.value().id()));
            break;
        }
        case TaskActionResult::FAIL_NO_SUCH_TASK: {
            printer_->WriteError("No parent task with this id was found.");
            break;
        }
        default: {
            printer_->WriteError("Invalid task was given, try again.");
            break;
        }
    }
}
