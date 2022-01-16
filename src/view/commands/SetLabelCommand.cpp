//
// Created by Maksym Kharchenko on 21.12.2021.
//

#include "SetLabelCommand.h"

SetLabelCommand::SetLabelCommand(const TaskId& task_id,
                                 const std::string& label) :
                                 task_id_(task_id),
                                 label_(label) {

}

CommandResult SetLabelCommand::Execute(const std::shared_ptr<ModelController>& controller) {
    ControllerRequestResult set_label_result = controller->AddTaskLabel(task_id_, label_);

    return CommandResult::Create(set_label_result);
}
