//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "AddSubTaskCommand.h"

AddSubTaskCommand::AddSubTaskCommand(const Task& task,
                                     const TaskId& parent_id) :
                                     task_(task),
                                     task_parent_id_(parent_id) {

}

CommandResult AddSubTaskCommand::Execute(const std::shared_ptr<Controller>& controller) {
    auto add_subtask_result = controller->AddSubTask(task_, task_parent_id_);
    switch(add_subtask_result.first) {
        case TaskActionResult::SUCCESS: {
            return CommandResult::Create(add_subtask_result.second.value());
        }
        default: {
            return CommandResult::Create(add_subtask_result.first);
        }
    }
}
