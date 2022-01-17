//
// Created by Maksym Kharchenko on 17.01.2022.
//

#include "RemoveLabelCommand.h"

RemoveLabelCommand::RemoveLabelCommand(const TaskId& task_id, const std::string& label) : task_id_(task_id), label_(label) {

}

CommandResult RemoveLabelCommand::Execute(const std::shared_ptr<ModelController> &controller) {
    ControllerRequestResult set_label_result = controller->RemoveTaskLabel(task_id_, label_);

    return CommandResult::Create(set_label_result);
}
